#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void ReadInGrammar(string file, vector<string>& rules)    // Szabályok beolvasása fájlból
{
      string line;
      ifstream input;
      input.open(file);
      while (getline(input, line))
      {
          rules.push_back(line);
      }
}

bool RecognizeString(vector<string>& rules, string word) // Itt vizsgáljuk meg, hogy a bemenet levezethető-e
{
      int wordLength, rulesSize, a, b, c, d;

      wordLength = word.length();
      rulesSize = rules.size();

      vector<vector<vector<bool>>> deriv(wordLength + 1, vector<vector<bool>>(wordLength + 1, vector<bool>(26, false))); // Vektor mátrixot hozunk létre, vizsgálat utáni értékek kerülnek ide

      for (a = 0; a < wordLength; ++a)
      {
            for (c = 0; c < rulesSize; ++c)
            {
                  if (rules[c].length() == 4 && rules[c][3] == word[a]) // A->C formájú szabályok vizsgálása
                  {
                      deriv[1][a][rules[c][0] - 'A'] = true;
                  }
            }
      }

      for (d = 2; d <= wordLength; ++d)
      {
            for (a = 0; a < wordLength - d + 1; ++a)
            {
                  for (b = 1; b <= d - 1; ++b)
                  {
                        for (c = 0; c < rulesSize; ++c)
                        {
                              if (rules[c].length() == 5 && deriv[b][a][rules[c][3] - 'A'] && deriv[d - b][a + b][rules[c][4] - 'A']) // A->BC formájú szabályok vizsgálása
                              {
                                  deriv[d][a][rules[c][0] - 'A'] = true;
                              }
                        }
                  }
            }
      }

      return deriv[wordLength][0]['S' - 'A']; // Visszaadja bool értékként, hogy levezethető-e a szó

}
  
int main()
{
      vector<string> rules;     // A rules.txt fájlban szerkeszthetőek a szabályok
      string word = "aabb";  // Itt adjuk meg a vizsgálandó szót

      ReadInGrammar("rules.txt", rules);

      cout << endl << "Rules:" << endl << endl;

      for (int c = 0; c < rules.size(); ++c)
      {
            cout << rules[c] << endl;
      }

      cout << endl << "The word to be examined: " + word << endl;

      if (RecognizeString(rules, word))
            cout << endl << "Success!" << endl << "This word (string) can be derivated and is part of the grammar! :)" << endl;
      else
            cout << endl << "Failure!" << endl << "This word (string) can not be derivated and is not part of the grammar! :(" << endl;
}