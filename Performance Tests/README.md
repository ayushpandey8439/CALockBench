Command line parameters for locking version are:
--help (-?) - prints help
--fileName (-f) <file_name> - sets options file name
--readOnlyPercent (-p) <number> - set percent of read-only operations
--workloadType (-w) r|rw|w - set workload type
--traversals (-t) true|false - enable/disable long traversals
--structuralModifications (-m) true|false - enable/disable structural modifications
--threadNum (-n) <number> - set number of simultaneous threads
--size (-s) s|m|b - set size of data structure
--lockType (-l) n|c|m|f - set locking type


Example usage:

		./sb7_lock -s b -l m -n 12 -w rw -d 120000

It will run sb7_lock on a big data structure, using medium grained locking,
with twelve concurrent threads, running a read/write workload for two minutes
with long traversals turned on.

Note: Fine grained locking is not implemented yet.
