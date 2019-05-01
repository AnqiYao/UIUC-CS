#include "simplecache.h"

int SimpleCache::find(int index, int tag, int block_offset) {
  // read handout for implementation details
 	auto a = _cache.find(index);	
	for (auto b: a->second){
		if (b.valid() == true && b.tag() == tag)
			return b.get_byte(block_offset);
		}
  return 0xdeadbeef;
}

void SimpleCache::insert(int index, int tag, char data[]) {
	std::vector<SimpleCacheBlock> &cache = _cache[index];
	for(int i = 0; i < cache.size(); i++){
		if(cache[i].valid() == false){
			cache[i].replace(tag, data);
			return;
											}
										}											
		cache[0].replace(tag, data);
  // read handout for implementation details
  // keep in mind what happens when you assign in in C++ (hint: Rule of Three)
}
