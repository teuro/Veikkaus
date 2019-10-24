#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <cmath>

int main() {
    std::default_random_engine generator (std::time(NULL));
    std::srand(std::time(NULL));
    std::normal_distribution <double> palautusjakauma (0.95, 0.07);
    std::normal_distribution <double> panosjakauma (225.85, 61.15);
    
    std::map <double, double> tulokset;
    
    double maksimi_tappio = 0;
    double maksimi_voitto = 0;
    
    for (int i = 0; i < 1000; ++i) {
        int pelikerrat = 3 + (std::rand() / (float)RAND_MAX) * (15 - 3);
        
        double peli_raha = panosjakauma(generator);
        
        double t_raha = peli_raha;
        double tulos = 0;
        tulokset[peli_raha] = 0;
        
        for (int j = 0; j < pelikerrat; ++j) {
            tulos = palautusjakauma(generator) * peli_raha - peli_raha;
            
            peli_raha += tulos;
        }
        
        tulokset[t_raha] = peli_raha;
    }
    
    std::map <double, double> :: iterator it = tulokset.begin();
    
    double pelattu = 0;
    double valitulos = 0;
    double kokonaistulos = 0;
    
    while (it != tulokset.end()) {
        pelattu += it->first;
        valitulos = (it->second - it->first);
        
        kokonaistulos += valitulos;
        
         if (valitulos > maksimi_voitto) {
            maksimi_voitto =  valitulos;
        } else if (valitulos < maksimi_tappio) {
            maksimi_tappio = valitulos;
        }
        
        ++it;
    }
    
    std::cout << "Yhteensä pelattiin " << pelattu << " euroa, josta tuli " << kokonaistulos << " euroa" << std::endl;
    std::cout << "maksimi tappio = " << maksimi_tappio << " maksimi voitto = " << maksimi_voitto << std::endl;
    
    return 0;
}
