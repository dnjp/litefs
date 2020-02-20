# LiteFS

## What is LiteFS?

LiteFS is a command line application that cryptographically verifies and serves
text content in your web browser. You use it by adding a directory to your local
database and then selecting the hash of the content you want LiteFS to serve.

For example, I can add the `sample` directory in this repository with `lfs add ./sample`. LiteFS will then recursively parse the text files in the directory
and construct a [SHA256](https://en.wikipedia.org/wiki/SHA-2) hashed [merkle
tree](https://en.wikipedia.org/wiki/Merkle_tree) with the contents. The output
of this command will look like the following:

```
root hash: 5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831
tree size: 4
file: <path to repository>/sample/contact.txt
    4611E497F75197329529C008CD24870537EF4D25CFD4C7A00FE6EE7509564209

file: <path to repository>/sample/dir/example.txt
    F5425CC8E871BC92F8AC98C75F0D476E616F39D7F06C524C0977B7668E65C7C7

file: <path to repository>/sample/thankyou.txt
    59D18234574B211D25FC5D224F85CC8687525CEC19190F7864C2081712A17A9E
```

Once I've added this directory, I can run `lfs status` to show the contents in
my local database, which will print a message like this:

```
{
    "5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831": {
        "contents": [
            {
                "content_hash": "4611E497F75197329529C008CD24870537EF4D25CFD4C7A00FE6EE7509564209",
                "content_path": "<path to repository>/sample/contact.txt"
            },
            {
                "content_hash": "F5425CC8E871BC92F8AC98C75F0D476E616F39D7F06C524C0977B7668E65C7C7",
                "content_path": "<path to repository>/sample/dir/example.txt"
            },
            {
                "content_hash": "59D18234574B211D25FC5D224F85CC8687525CEC19190F7864C2081712A17A9E",
                "content_path": "<path to repository>/sample/thankyou.txt"
            }
        ],
        "root_path": "<path to repository>/sample"
    }
}
```

Then I can serve the content for this root hash with the command `lfs serve 5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831` which will
verify that the contents of the directory being served have not changed. If
they haven't changed, it will print this message:

```
verifying contents of hash 5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831

serving root at http://localhost:3000/5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831

serving at localhost:3000/

contents:

localhost:3000/4611E497F75197329529C008CD24870537EF4D25CFD4C7A00FE6EE7509564209
localhost:3000/F5425CC8E871BC92F8AC98C75F0D476E616F39D7F06C524C0977B7668E65C7C7
localhost:3000/59D18234574B211D25FC5D224F85CC8687525CEC19190F7864C2081712A17A9E
localhost:3000/5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831

```

If I open my browser to the root location, which here is
`http://localhost:3000/5A826CAAE5EC0B00715C2AA531A609B9A723331C6D1582607D3B5D00D1578831`,
I will see a web page with links to the rest of the content being served.

## Dependencies

- cmake >= 3.9.3
- make >= 4.1 (Linux, Mac), 3.81 (Windows)
- gcc/g++ >= 5.4

## Building

- git clone git@github.com:danieljamespost/litefs.git --recursive
- make build
- make install

## Usage

```
lfs <command> <args>

These are the common lfs commands:

    add    <directory>   Add directory to the local database of verified hashed contents.

    status               List the hashed content that is currently stored.

    rm     <hash>        Remove the content with selected hash from database.

    serve  <hash>        Serve the content with specified hash for network access

    help                 Show usage message.

```

## Project Structure

Each component of LiteFS is split into its own internal library which
encapsulates its functionality. Here is a partial output of the `tree` command
to show how this is structured.

```
├── cli
│   ├── CMakeLists.txt
│   ├── include
│   │   └── cli
│   │       ├── cli.h
│   │       ├── conf.h
│   │       ├── config.h
│   │       └── db.h
│   └── src
│       ├── cli.cc
│       ├── config.cc
│       └── db.cc
├── CMakeLists.txt
├── lfs
│   ├── CMakeLists.txt
│   └── main.cc
├── Makefile
├── merkle_tree
│   ├── CMakeLists.txt
│   ├── include
│   │   └── merkle
│   │       ├── content.h
│   │       ├── hash.h
│   │       ├── node.h
│   │       └── tree.h
│   └── src
│       ├── content.cc
│       ├── hash.cc
│       ├── node.cc
│       └── tree.cc
```

The `merkle_tree` library is the focal point of the project. Within
`merkle_tree` you'll find the `MerkleTree` class in `tree.h` which contains a
vector of `unique_ptrs` (line 35) to the `Node` class (found in `node.h`).
`Node` contains the `Content` (defined in `content.h`) and holds data handles to
the `MerkleTree`, parent, left, and right `Nodes` and its own `hash`. `Node`
also contains multiple constructors for instantiating leaf `Nodes` and `Nodes` as a duplicate
of another `Node` (lines 14 & 15 in `node.h`). `Content`
in turn holds the `Hash` (defined in `hash.h`) and functions for comparison,
and accessing the hash.

The `cli` library is focused on capturing user input (line 243 of `cli.cc`),
reading (line 8 of `db.cc`) and writing data (line 15). The `Config` class
inherits from `DB` and implements the functionality of `DB` to read and write the
configuration file for LiteFS.
