Select DISTINCT player_id , MIN(EVENT_DATE) as first_login 
from activity 
Group by player_id;
