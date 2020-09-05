The implementation of the General Tree needs optimization. Because it is simple implementation,
that for example adds new child at the first match of the node that is looked for. Also the odd filter
deletes the whole subtree, while for an optimization it could just delete the node and create new subtree.
If we add some sort of constraint we can make the tree faster when adding/searching/deleting nodes.