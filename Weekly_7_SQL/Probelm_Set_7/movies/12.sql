SELECT DISTINCT movies.title
FROM movies
JOIN stars AS sc ON movies.id = sc.movie_id
JOIN people AS bradley_cooper ON sc.person_id = bradley_cooper.id
JOIN stars AS sj ON movies.id = sj.movie_id
JOIN people AS jennifer_lawrence ON sj.person_id = jennifer_lawrence.id
WHERE (bradley_cooper.name = 'Bradley Cooper' AND jennifer_lawrence.name = 'Jennifer Lawrence');