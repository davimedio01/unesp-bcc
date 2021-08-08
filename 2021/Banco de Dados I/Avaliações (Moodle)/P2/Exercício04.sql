rem Realização de Divisão = "por todos os" pilotos BRASILEIROS
select anome
from autodromo aut
where not exists(select pnum
                 from piloto
                 where pnacionalidade = 'Brasileira'
                
                 minus
                
                 select pnum
                 from corrida
                 where anum = aut.anum)
and exists      (select pnum
                 from piloto
                 where pnacionalidade = 'Brasileira');
