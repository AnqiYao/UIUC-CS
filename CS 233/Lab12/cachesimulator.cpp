#include "cachesimulator.h"
using namespace std;
using std::vector;
Cache::Block* CacheSimulator::find_block(uint32_t address) const {
  /**
   * TODO
   *
   * 1. Use `_cache->get_blocks_in_set` to get all the blocks that could
   *    possibly have `address` cached.
   * 2. Loop through all these blocks to see if any one of them actually has
   *    `address` cached (i.e. the block is valid and the tags match).
   * 3. If you find the block, increment `_hits` and return a pointer to the
   *    block. Otherwise, return NULL.
   */
	const CacheConfig& _cache_config = _cache->get_config();
	int index = extract_index(address,_cache_config);
	int tag = extract_tag(address,_cache_config);
	std::vector<Cache::Block*> a = _cache->get_blocks_in_set(index);
	for(int i = 0; i < a.size(); i++){
		if(a[i]->is_valid() && a[i]->get_tag() == tag)
		{
		_hits++;
		return a[i];
		}
	}
	
	
  return NULL;
}

Cache::Block* CacheSimulator::bring_block_into_cache(uint32_t address) const {
  /**
   * TODO
   *
   * 1. Use `_cache->get_blocks_in_set` to get all the blocks that could
   *    cache `address`.
   * 2. Loop through all these blocks to find an invalid `block`. If found,
   *    skip to step 4.
   * 3. Loop through all these blocks to find the least recently used `block`.
   *    If the block is dirty, write it back to memory.
   * 4. Update the `block`'s tag. Read data into it from memory. Mark it as
   *    valid. Mark it as clean. Return a pointer to the `block`.
   */
	const CacheConfig& _cache_config = _cache->get_config();
  	int index = extract_index(address, _cache_config);
	int tag = extract_tag(address, _cache_config);	
	vector<Cache::Block*> b = _cache->get_blocks_in_set(index);
	Cache::Block* c = b[0];
	int least = b[0]->get_last_used_time();
	for(int i = 0; i < b.size(); i++){
		if (b[i]->is_valid() == false){
			b[i]->set_tag(tag);
			b[i]->read_data_from_memory(_memory);
			b[i]->mark_as_valid();
			b[i]->mark_as_clean();
			return b[i];
		}
		if(least > b[i]->get_last_used_time()){
			least = b[i]->get_last_used_time();
			c = b[i];
		}
	}		
	if(c->is_dirty() == true)
		c ->write_data_to_memory(_memory);
	c->set_tag(tag);
	c->read_data_from_memory(_memory);		
	c->mark_as_valid();
	c->mark_as_clean();
  return c;
}

uint32_t CacheSimulator::read_access(uint32_t address) const {
  /**
   * TODO
   *
   * 1. Use `find_block` to find the `block` caching `address`.
   * 2. If not found, use `bring_block_into_cache` cache `address` in `block`.
   * 3. Update the `last_used_time` for the `block`.
   * 4. Use `read_word_at_offset` to return the data at `address`.
   */
	Cache::Block* d = find_block(address);
	if (d == NULL)
		d = bring_block_into_cache(address);	
	_use_clock++;
	d->set_last_used_time(_use_clock.get_count());
	const CacheConfig& _cache_config = _cache->get_config();
	return d->read_word_at_offset(extract_block_offset(address, _cache_config));
}

void CacheSimulator::write_access(uint32_t address, uint32_t word) const {
  /**
   * TODO
   *
   * 1. Use `find_block` to find the `block` caching `address`.
   * 2. If not found
   *    a. If the policy is write allocate, use `bring_block_into_cache`.
   *    a. Otherwise, directly write the `word` to `address` in the memory
   *       using `_memory->write_word` and return.
   * 3. Update the `last_used_time` for the `block`.
   * 4. Use `write_word_at_offset` to to write `word` to `address`.
   * 5. a. If the policy is write back, mark `block` as dirty.
   *    b. Otherwise, write `word` to `address` in memory.
   */
	
	Cache::Block* p = find_block(address);
	if ( p == NULL ) {
		if ( _policy.is_write_allocate())
			p = bring_block_into_cache(address);
		else {
			_memory->write_word(address,word);
 			return;
			}
		}
	_use_clock++;
	p->set_last_used_time(_use_clock.get_count());
	const CacheConfig& _cache_config = _cache->get_config();
	 p->write_word_at_offset(word,extract_block_offset(address, _cache_config));
	if (_policy.is_write_back())
		p->mark_as_dirty();
	else
		p->write_data_to_memory(_memory);

	return;
}			
	
