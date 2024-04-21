CREATE TABLE IF NOT EXISTS "files" (
        "file_id"	INTEGER,
        "research_id"	INTEGER NOT NULL,
        "file_name"	TEXT NOT NULL,
        "file_data"	BLOB,
        PRIMARY KEY("file_id" AUTOINCREMENT)
);
