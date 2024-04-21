CREATE TABLE IF NOT EXISTS "keyword_def" (
        "keyword_def_id"	INTEGER,
        "keyword_def"	TEXT NOT NULL UNIQUE,
        PRIMARY KEY("keyword_def_id" AUTOINCREMENT)
);
