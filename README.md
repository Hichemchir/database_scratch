# database_scratch

A lightweight key-value database implementation in C++ with write-ahead logging (WAL) for durability.

## Features

- **Key-Value Store**: Simple API for set, get, delete operations
- **Write-Ahead Log (WAL)**: Binary log format with CRC32 checksums for data integrity
- **Persistent Storage**: Durable storage to disk with crash recovery
- **Interactive CLI**: Command-line interface for database operations

## Architecture

```
┌─────────────────────────────────────┐
│            Database                 │
│  API: set, get, del, exists         │
├─────────────────────────────────────┤
│            KVStore                  │
│     (in-memory hash map)            │
├─────────────────────────────────────┤
│    WAL (Write-Ahead Log)            │
│       (durability)                  │
├─────────────────────────────────────┤
│         Storage                     │
│    (disk persistence)               │
└─────────────────────────────────────┘
```

## WAL Format

Each record in the write-ahead log follows this binary format:

```
| CRC32 (4 bytes) | Type (1 byte) | KeyLen (4) | ValLen (4) | Key | Value |
```

- **CRC32**: Checksum for data integrity verification
- **Type**: Operation type (SET or DEL)
- **KeyLen/ValLen**: Length of key and value in bytes
- **Key/Value**: Actual data

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

Run the CLI:

```bash
./database_scratch
```

Available commands:

- `set <key> <value>` - Store a key-value pair
- `get <key>` - Retrieve value for a key
- `del <key>` - Delete a key
- `exists <key>` - Check if a key exists
- `clear` - Clear the screen
- `help` - Show available commands
- `exit` - Quit the program

## Project Structure

```
database_scratch/
├── include/
│   ├── cli.hpp
│   └── db/
│       ├── common.hpp
│       ├── database.hpp
│       ├── kv_store.hpp
│       ├── storage.hpp
│       └── wal.hpp
├── src/
│   ├── main.cpp
│   ├── cli/
│   │   └── cli.cpp
│   └── db/
│       ├── database.cpp
│       ├── kv_store.cpp
│       ├── storage.cpp
│       └── wal.cpp
└── tests/
    └── test_database.cpp
```

## Requirements

- C++20 compatible compiler
- CMake 3.15 or higher

## License

MIT