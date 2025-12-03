# database_scratch

Schema idea of the db:
             ┌───────────────────────────────────┐
             │             Database               │
             └───────────────┬───────────────────┘
                             │
                      API: set, get, del
                             │
             ┌───────────────┴───────────────────┐
             │               KVStore              │
             └───────────────┬───────────────────┘
                             │
                             ▼
                 ┌────────────────────┐
                 │   WAL (write-ahead)│   <── durability
                 └────────────────────┘
                             │
                             ▼
                 ┌────────────────────┐
                 │   MemTable (RAM)   │   <── fast operations
                 └────────────────────┘
                             │
                             ▼
             ┌──────────────────────────────────────┐
             │        SSTable (sorted, immutable)    │ <── disk compaction
             ────────────────────-───────────────────┘

# For the Write ahead log:

| CRC32 (4 bytes) | Type (1 byte) | KeyLen (4) | ValLen (4) | Key | Value |
