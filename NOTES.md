Specifying a directory to search should open up a new user *Session*.  
The *Session* has a *Metadata Processor*, which will determine whether a path is valid
as well as recursively analyze the files and produce the data structure representing the processed file metadata.  

The list of options for metadata processing:
    - file types/categories (choose to ignore or include)
    - file extensions (choose to ignore or include)
should be globally represented and available to the *Session*, so it can show those options in the UI.

These options should be read and applied before a processing action occurs to save time on large file structures.


### Metadata Processor


### DB Adapter

Example opening sqlite3 db connection
```c++
sqlite3 *db;
char zErrMsg = 0;

int rc;
rc = sqlite3_open(DB_NAME, &db);
if( rc == SQLITE_OK ) {
    printf("Opened database.\n");
}
if( db == NULL ) {
    printf("[ERROR]: Unable to allocate memory for db.\n");
}
```

