#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <algorithm>
#include <iostream>
#include <list>
#include <cstring>
using namespace std;

int n;

string command,card;

int main() {
  list<string> pile;
  cin >> n;

  for (int i = 0; i < n; i++) 
  {
    // cin >> card >> command;
    cin >> command;
    if (command == "add") 
    {
      cin >> card;
      pile.emplace_front(card);

    } 
    else if (command == "delete") 
    {
      cin >> card;
      auto itr = find(pile.begin(), pile.end(), card);

      if (itr == pile.end()) 
      {
        continue;
      }
      pile.erase(itr);

      // pile.erase()
    } 
    else if (command == "truncateFirst") 
    {
      pile.pop_front();

    } 
    else if (command == "truncateLast") 
    {
      pile.pop_back();
    }
  }

  for (const auto &item : pile) 
  {
    cout << item << ' ';
  }
  cout << endl;

  return 0;
}