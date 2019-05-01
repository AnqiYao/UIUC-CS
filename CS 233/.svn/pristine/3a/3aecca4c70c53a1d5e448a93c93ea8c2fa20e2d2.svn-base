#include "utils.h"

uint32_t extract_tag(uint32_t address, const CacheConfig& cache_config) {
	if (cache_config.get_num_tag_bits() >=32)
		return address;
  int a = cache_config.get_num_index_bits() + cache_config.get_num_block_offset_bits();
  return address>>a;
}

uint32_t extract_index(uint32_t address, const CacheConfig& cache_config) {
  if (cache_config.get_num_tag_bits() >=32)
		return 0;
  return (address<< cache_config.get_num_tag_bits()) >> (cache_config.get_num_tag_bits()+cache_config.get_num_block_offset_bits());
}

uint32_t extract_block_offset(uint32_t address, const CacheConfig& cache_config) {
  if (cache_config.get_num_tag_bits() >=32)
		return 0;
  return (address<<(cache_config.get_num_index_bits()+ cache_config.get_num_tag_bits()))>> (cache_config.get_num_index_bits()+ cache_config.get_num_tag_bits());
}
