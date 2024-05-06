SELECT research.title, research.research_id FROM research
INNER JOIN keyword_def ON keyword_def.keyword_def_str LIKE '%%1%'
INNER JOIN keywords ON keywords.keyword_def_id = keyword_def.keyword_def_id
AND research.research_id = keywords.research_id;
