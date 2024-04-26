CREATE TABLE IF NOT EXISTS "keyword_def" (
        "keyword_def_id"	INTEGER,
        "keyword_def_str"	TEXT NOT NULL UNIQUE,
        PRIMARY KEY("keyword_def_id" AUTOINCREMENT)
);
