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

- A variety of control structures are used in the project.
  Any of the \*.cc source files

- The project code is clearly organized into functions.
  Any of the \*.cc source files

- The project reads data from an external file or writes data to a file as part
  of the necessary operation of the program.
  line 37 & 48 of `db.cc`

- The project accepts input from a user as part of the necessary operation of
  the program.
  line 17 of `cli.cc`

- The project code is organized into classes with class attributes to hold the
  data, and class methods to perform tasks.
  See diagram above

- All class data members are explicitly specified as public, protected, or
  private.
  See any of the \*.h source files

- All class members that are set to argument values are initialized through
  member initialization lists.
  See lines 20, 29, and 42 of `node.h` and line 18 of `content.h`

- All class member functions document their effects, either through function
  names, comments, or formal documentation. Member functions do not change
  program state in undocumented ways.
  See inline documentation in all source files

- Appropriate data and functions are grouped into classes. Member data that is
  subject to an invariant is hidden from the user. State is accessed via member
  functions.
  See any of the \*.h source files

- Inheritance hierarchies are logical. Composition is used instead of
  inheritance when appropriate. Abstract classes are composed of pure virtual
  functions. Override functions are specified.
  See `tree.h`, `db.h`, and `config.h`

- One function is overloaded with different signatures for the same function
  name.
  See multiple constructors for the `Node` class in `node.h`

- One member function in an inherited class overrides a virtual base class
  member function.
  See lines 38-42 in `db.h`

- One function is declared with a template that allows it to accept a generic
  parameter.
  **TODO**

- At least two variables are defined as references, or two functions use
  pass-by-reference in the project code.
  See line 92 & 127 in `tree.cc`

- At least one class that uses unmanaged dynamically allocated memory, along
  with any class that otherwise needs to modify state upon the termination of an
  object, uses a destructor.
  Not needed

- The project follows the Resource Acquisition Is Initialization pattern where
  appropriate, by allocating objects at compile-time, initializing objects when
  they are declared, and utilizing scope to ensure their automatic destruction.
  See lines 27-34 of `server.h`

- For all classes, if any one of the copy constructor, copy assignment operator,
  move constructor, move assignment operator, and destructor are defined, then
  all of these functions are defined.

  Not needed

- For classes with move constructors, the project returns objects of that class
  by value, and relies on the move constructor, instead of copying the object.
  Not needed

- The project uses at least one smart pointer: unique_ptr, shared_ptr, or
  weak_ptr. The project does not use raw pointers.
  See `_leafs` in `tree.h` and `tree.cc`

* The project uses multiple threads in the execution.
  See line 155 in `cli.cc`

* A promise and future is used to pass data from a worker thread to a parent
  thread in the project code.

* A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect
  data that is shared across multiple threads in the project code.

  See line 194 of `cli.cc`

* A std::condition_variable is used in the project code to synchronize thread
  execution.

  See line 195 of `cli.cc`
