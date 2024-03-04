As of 2024/3/4:

- `ordered_set_base`:
  - encapsulate the first four field of `node` in a class and provide getter funcs for them
  - provide iterator behaviour 
    - Q: should `end()` return `NULL_NODE?` 
    - A: No!
  - move most function described in this class to `cpdsa::dynamic_segment_tree_base<_Tp,...>`

- `dynamic_segment_tree`:
  - still waiting ... 