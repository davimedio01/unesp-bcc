select cor.cnum, pil.pnome, aut.anome
from corrida cor, autodromo aut, piloto pil
where cor.pnum = pil.pnum and cor.anum = aut.anum
order by cor.cnum asc;