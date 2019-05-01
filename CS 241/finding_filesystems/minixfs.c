/**
* Finding Filesystems Lab
* CS 241 - Spring 2018
*/

#include "minixfs.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int minixfs_chmod(file_system *fs, char *path, int new_permissions) {
    // Thar she blows!
	inode *temp = get_inode(fs,path);
	if(!temp){
		errno = ENOENT;
		return -1; //the file doesn't exist
	}
	temp->mode = (temp->mode >> RWX_BITS_NUMBER << RWX_BITS_NUMBER)| new_permissions;
	struct timespec curr;
	int res = clock_gettime(CLOCK_REALTIME, &curr);
    	if(res == -1){
      		return -1;
    	}
	temp->ctim = curr;
	return 0;
}

int minixfs_chown(file_system *fs, char *path, uid_t owner, gid_t group) {
    // Land ahoy!
	inode *temp = get_inode(fs,path);
        if(!temp){
                errno = ENOENT;
                return -1; //the file doesn't exist
        }
	if(owner != ((uid_t)-1)){
		temp->uid = owner;
	}
	if(group != ((gid_t)-1)){
                temp->gid = group;
        }
	struct timespec curr;

        int res = clock_gettime(CLOCK_REALTIME, &curr);
	if(res == -1){
                return -1;
        }
        temp->ctim = curr;
    	return 0;
}



ssize_t minixfs_write(file_system *fs, const char *path, const void *buf,
                      size_t count, off_t *off) {
    // X marks the spot
    inode* n = get_inode(fs, path);
    if(n == NULL){
      n = minixfs_touch(fs, path);
    }
    size_t total_size = (NUM_INDIRECT_INODES+NUM_DIRECT_INODES) * 16 * KILOBYTE;
    if(total_size < (count+ (size_t)(*off))){
      errno = ENOSPC;
      return -1;
    }
    int min_block = (int)(*off)/(size_t)(16 * KILOBYTE)+1;
    int aloc = minixfs_min_blockcount(fs, path, min_block);
    if(aloc == -1){
      errno = ENOSPC;
      return -1;
    }
    size_t write_size = count;
    size_t offset = (size_t)*off % (16 * KILOBYTE);
    size_t buf_idx = 0;
    data_block_number block_num = 0;
    int flag = 1;
    while(min_block <= NUM_DIRECT_INODES){
      block_num = n->direct[min_block-1];
      if(write_size + offset <= (size_t)(16 * KILOBYTE)){
        memcpy(((fs->data_root)+block_num)->data+offset, buf+buf_idx, write_size);
        buf_idx+=write_size;
        offset = 0;
        flag = 0;
        break;
      }
      else{
        memcpy(((fs->data_root)+block_num)->data+offset, buf+buf_idx, 16 * KILOBYTE - offset);
        buf_idx+=16 * KILOBYTE - offset;
        write_size -= 16 * KILOBYTE - offset;
        offset = 0;
        min_block++;
        flag = 2;
        if(min_block <= NUM_DIRECT_INODES){
          block_num = add_data_block_to_inode(fs, n);
          if(block_num == -1){
            errno = ENOSPC;
            return -1;
          }
        }
      }
    }
    int in_min_block = 0;
    if(flag!=0){
      data_block_number in_num = 0;
      if(flag == 1){
        int surpass_idx = min_block - NUM_DIRECT_INODES - 1;
         in_num= ((fs->data_root)+n->indirect)->data[surpass_idx*4];
         in_min_block+=min_block - NUM_DIRECT_INODES;
      }
      else{
         inode_number n_id = add_single_indirect_block(fs, n);
         if(n_id == -1){
           errno = ENOSPC;
           return -1;
         }
         in_num = add_data_block_to_indirect_block(fs, &(n->indirect));
         in_min_block++;
       }
        while(write_size > 0){
          if(write_size + offset <= (size_t)(16 * KILOBYTE)){
            memcpy(((fs->data_root)+in_num)->data+offset, buf+buf_idx, write_size);
            buf_idx+=write_size;
            break;
          }
          else{
            memcpy(((fs->data_root)+in_num)->data+offset, buf+buf_idx, 16 * KILOBYTE - offset);
            buf_idx+=16 * KILOBYTE - offset;
            write_size -= 16 * KILOBYTE - offset;
            offset = 0;
            in_min_block++;
            if(write_size > 0){
            in_num = add_data_block_to_indirect_block(fs, &(n->indirect));
            if(in_num == -1){
              errno = ENOSPC;
              return -1;
            }
          }
        }
      }
    }
    if(min_block > NUM_DIRECT_INODES){
      min_block = NUM_DIRECT_INODES;
    }
    uint64_t new_size = 16 * KILOBYTE * (min_block + in_min_block) + write_size;
    if(new_size > n->size){
      n->size = new_size;
    }
    *off+=(off_t)count;
    struct timespec atime;
    int res1 = clock_gettime(CLOCK_REALTIME, &atime);
    if(res1 == -1){
      return -1;
    }
    n->atim = atime;
    struct timespec mtime;
    int res2 = clock_gettime(CLOCK_REALTIME, &mtime);
    if(res2 == -1){
      return -1;
    }
    n->mtim = mtime;
    return (ssize_t)count;
}

ssize_t minixfs_read(file_system *fs, const char *path, void *buf, size_t count,
                     off_t *off) {
    // 'ere be treasure!
    inode* n = get_inode(fs, path);
    if(n == NULL){
      errno = ENOENT;
      return -1;
    }
    size_t total_size = n->size;
    if((size_t)*off>total_size){
      return 0;
    }
    if(total_size < count + (size_t)*off){
      count = total_size - (size_t)*off;
    }
    int min_block = (int)(*off)/(size_t)(16 * KILOBYTE) + 1;
    size_t read_size = count;
    size_t offset = (size_t)*off - (min_block-1) * 16 * KILOBYTE;
    size_t buf_idx = 0;
    data_block_number block_num = 0;
    int flag = 1;
    while(min_block <= NUM_DIRECT_INODES){
      block_num = n->direct[min_block-1];
      if(read_size+offset <= (size_t)(16 * KILOBYTE)){
        memcpy(buf+buf_idx, ((fs->data_root)+block_num)->data+offset, read_size);
        buf_idx+=read_size;
        offset = 0;
        flag = 0;
        break;
      }
      else{
        memcpy(buf+buf_idx, ((fs->data_root)+block_num)->data+offset, 16 * KILOBYTE - offset);
        buf_idx+=16 * KILOBYTE - offset;
        read_size -= 16 * KILOBYTE - offset;
        offset = 0;
        flag = 2;
        min_block++;
      }
    }
    data_block_number in_num = 0;
    if(flag!=0){
      int idx = 0;
      if(flag == 1){
        idx = min_block - NUM_DIRECT_INODES - 1;
      }
      while(read_size > 0){
        in_num = ((fs->data_root)+n->indirect)->data[idx*4];
        if(read_size+offset <= (size_t)(16 * KILOBYTE)){
            memcpy(buf+buf_idx, ((fs->data_root)+in_num)->data+offset, read_size);
            buf_idx+=read_size;
            break;
        }
        else{
          memcpy(buf+buf_idx, ((fs->data_root)+in_num)->data+offset, 16 * KILOBYTE - offset);
          buf_idx+=16 * KILOBYTE - offset;
          read_size -= 16 * KILOBYTE -offset;
          offset = 0;
          idx++;
        }
      }
    }
    *off+=(off_t)count;
    struct timespec atime;
    int res1 = clock_gettime(CLOCK_REALTIME, &atime);
    if(res1 == -1){
      return -1;
    }
    n->atim = atime;
    return count;
}

