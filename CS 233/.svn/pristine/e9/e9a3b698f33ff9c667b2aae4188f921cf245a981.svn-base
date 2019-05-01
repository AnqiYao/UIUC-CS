#include "cacheblock.h"

uint32_t Cache::Block::get_address() const {
	int a = get_tag();
	a = a << _cache_config.get_num_index_bits();
	a += _index;
	a = a << _cache_config.get_num_block_offset_bits();
  return a;
}
