// Comparator
bool compare(const std::pair<int, int>&a, const std::pair<int, int>&b) {
return a.first<b.first; // Ascending by first.
}

sort(nums.begin(), nums.end());
stable_sort(nums.begin(), nums.end());
nth_element(nums.begin(), nums.begin()+k, nums.end());
// nth_element does not sort the other positions.
binary_search(nums.begin(), nums.end(), x);
next_permutation(nums.begin(), nums.end());
prev_permutation(nums.begin(), nums.end());
accumulate(nums.begin(), nums.end(), 0LL);
iota(nums.begin(), nums.end(), 0);
nums.erase(unique(nums.begin(), nums.end()), nums.end());
// Sort first if removing all duplicate values.
min_element(nums.begin(), nums.end());
max_element(nums.begin(), nums.end());
