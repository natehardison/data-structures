`sll`: a singly-linked list module
=

There are two main parts to this module:

1. `node.h` is the implementation of a generic, singly-linked list node. This
is intended to provide the primary linked list operations, nothing more.
Those interested in manipulating a singly-linked list of values and not
dropping to this level should rely on the sll module.

2. `sll.h` is the implementation of a generic, singly-linked list. This serves
as a wrapper around the `node` module, which is where the primary linked list
operations are implemented. The idea is that clients of the `sll` module
are interested in manipulating values instead of `node`s, so we hide those
details from them.