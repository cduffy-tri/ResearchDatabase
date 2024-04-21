CREATE TABLE IF NOT EXISTS "research" (
        "research_id"	INTEGER,
        "title"	TEXT NOT NULL,
        "author"	TEXT,
        "publication_date"	TEXT,
        "abstraction"	TEXT,
        "doi"	TEXT,
        "url"	TEXT,
        PRIMARY KEY("research_id" AUTOINCREMENT)
);
