#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <sstream>
#include <map>

using namespace std; 

class solution{
private:
    // using PolyItem = std::pair<int, int>; 

    struct PolyItem{
        int coef = 0 , pow =0; 
        inline PolyItem(const int& coef , const int& pow){
            this->coef = coef ; 
            this->pow = pow ; 
        }

        std::string toString() const {
            if (!this->coef){
                return "";
            }

            std::string res = (this->coef > 0 ? "+" : "-") ;

            if (std::abs(this->coef) != 1){
                res += std::to_string(std::abs(this->coef));
            }

            if (!this->pow){
                return (this->coef > 1 ? res : std::to_string(this->coef));
            }

            if (this->pow == 1){
                return res + "x";
            }

            return res + "x^" + std::to_string(this->pow);
        }
    };
    using Poly = std::list<PolyItem>;
    using SuperPoly = std::map<int,int>;

    struct DecodeItem{
        int op  = 1 ;
        bool afterX = false ; 
        std::vector<std::string> item;


        inline DecodeItem(){
            this->init();
        }

        inline void init(){
            this->op = 1 ; 
            this->afterX = false;
            this->item.assign(2 , std::string());
        }

        inline bool itemIsEmpty() const {
            return this->item[0].empty() && this->item[1].empty();
        }

        inline PolyItem toPolyItem(const bool& afterX) {
            PolyItem res = {
                stoi((this->item[0].empty() ? "1" : this->item[0])) * op, 
                stoi((this->item[1].empty() ? to_string(afterX) : this->item[1]))
            }; 
            this->init();
            return res; 
        }
    };

public:
    inline Poly stringToPoly(const std::string& str){
        DecodeItem decodeItem; 
        Poly res ; 
        for (const auto& chr : str){
            // except
            if (chr == '^'){
                continue;
            }

            // operator
            if (chr == '+' || chr == '-') {
                
                if (!decodeItem.itemIsEmpty()){
                    res.push_back(decodeItem.toPolyItem(decodeItem.afterX));
                }

                else if (decodeItem.itemIsEmpty() && decodeItem.afterX){
                    decodeItem.item[0].push_back('1');
                    decodeItem.item[1].push_back('1');
                    res.push_back(decodeItem.toPolyItem(decodeItem.afterX));
                }
                decodeItem.op = (chr == '+' ? 1 : -1);
                continue;
            }

            // handle number
            if (chr >= '0' && chr <= '9'){
                decodeItem.item[int(decodeItem.afterX)].push_back(chr);
                continue;
            }

            if (chr == 'x'){
                decodeItem.afterX = true;
                continue;
            }
            
        }
        res.push_back(decodeItem.toPolyItem(decodeItem.afterX));
        return res;
    }

    inline static std::string polyToString(const Poly& poly) {
        std::string str ; 

        for (const auto& item : poly){
            str += item.toString();
        }

        if (str[0] == '+'){
            return std::string(str.begin() + 1 , str.end());
        }

        return str;
    }

    inline static SuperPoly polyToMap(const Poly& poly , const int& inv) {
        SuperPoly superPoly ; 

        for (const auto& item : poly){
            try{
                superPoly.at(item.pow) += item.coef * inv;
            }
            catch(const std::exception& e){
                superPoly.insert({item.pow , item.coef * inv});
            }
        }
        

        return superPoly;
    }

    inline static Poly mapToPoly(const SuperPoly& superPoly) {
        Poly poly;

        for (auto itr = superPoly.rbegin(); itr != superPoly.rend(); itr ++){
            poly.push_back({itr->second , itr->first});
        }

        return poly;
    }

    inline static SuperPoly add(const SuperPoly& superPoly1 , const SuperPoly& superPoly2){
        SuperPoly longSuperPoly = superPoly1, shortSuperPoly = superPoly2;

        if (superPoly1.size() < superPoly2.size()){
            longSuperPoly = superPoly2;
            shortSuperPoly = superPoly1;

        }

        for (const auto& item : shortSuperPoly){
            try{
                longSuperPoly.at(item.first) += item.second;

                if (longSuperPoly.at(item.first) == 0 ){
                    longSuperPoly.erase(item.first);
                }
            }
            catch(const std::exception& e){
                longSuperPoly.insert(item); 
            }
        }

        return longSuperPoly;
    }


public:
    inline void read() {
        string tmp ; 
        cin >> tmp ;
        this->poly1 = this->stringToPoly(tmp);

        cin >> tmp ;
        this->poly2 = this->stringToPoly(tmp);

        cin >> op ;
    }    

    inline void run(){
        // this->test();

        auto superPoly1 = solution::polyToMap(this->poly1 , 1);
        auto superPoly2 = solution::polyToMap(this->poly2 , (this->op == '-' ? -1 : 1));

        auto resSuperPoly = solution::add(superPoly1 , superPoly2);
        if (resSuperPoly.empty()){
            cout << "0\n"; 
            return ;
        }

        auto resPoly = solution::mapToPoly(resSuperPoly);

        cout << solution::polyToString(resPoly) << '\n';
    }

private:
    Poly poly1 , poly2 ; 
    char op; 
};


int main (){
    
    solution a; 
    a.read() ; 
    a.run();
    return 0 ; 
}