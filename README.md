    FRAUD TEST - Algoritmi i strukture podataka

Ovaj program čita podatke iz "fraudTest.csv" datoteke i sprema ih u mapu podataka. Podaci su predstavljeni kao redovi s 4 stupca. Korisnik može izvesti sljedeće funkcionalnosti:

- Ispis prvih n redaka - korisnik upisuje vrijednost parametra n.
- Ispis zadnjih n redaka - korisnik upisuje vrijednost parametra n.
- Pretraživanje podataka prema ključu - korisnik upisuje vrijednost ključa.
- Pretraživanje podataka prema vrijednosti u stupcu - korisnik upisuje vrijednost stupca.
- Brisanje podataka prema ključu - korisnik upisuje vrijednost ključa.
- Brisanje podataka prema vrijednosti u stupcu - korisnik upisuje vrijednost stupca.

    Uporaba
Prije pokretanja programa, u main funkciji korisnik treba odabrati koje od sljedećih metoda želi koristiti:

- get_min_values(n): ispis prvih n redaka
- get_top_values(n): ispis zadnjih n redaka
- search_by_key(key): pretraživanje podataka prema ključu
- search_by_value(value): pretraživanje podataka prema vrijednosti u stupcu
- delete_by_key(key): brisanje podataka prema ključu
- delete_by_value(value): brisanje podataka prema vrijednosti u stupcu

    Ograničenja
Program ja ograničen na prvih 500,000 redaka u csv datoteci. Također, program uzima samo 4 stupca iz CSV datoteke.
