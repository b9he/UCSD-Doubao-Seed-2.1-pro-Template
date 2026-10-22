// begin/end form [begin,end); end() is not dereferenceable.
// --begin() and ++end() are invalid.
// vec reallocation invalidates all iterators/references;
// erase invalidates those at/after the erased position.
// map/set insertion preserves iterators; erase invalidates
// only iterators/references to erased elements.
