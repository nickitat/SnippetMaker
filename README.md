# SnippetMaker
Provides you a short snippet of the given text by given queries.

### Препроцессинг
* Для каждого предложения текста считается его априорный вес ![alt text](http://mathurl.com/l8vjsoc.png "Априорный вес предложения"),
мы полагаем ![alt text](http://mathurl.com/m63n2my.png "Априорный вес слова") равным количеству вхождений ![alt text](http://mathurl.com/lf4bkau.png)
в текст. Таким образом, лучше то предложение, которое меньше весит.
* Из этого получается `unordered_map<string, vector<int>> sentencesWithThisWord`, в которой для каждого слова текста сохранены
первые _К_ самых легких предложений, в которые оно входит.
Это _К_ в коде передается вторым параметром в констуктор `DataPreparator(wifstream &input, int _MAX_SENTENCES_COUNT)`.

Все это работает за ![alt text](http://mathurl.com/nx9meya.png "Сложность препроцессинга"),
где _Т_ - длина текста, _W_ - количество слов в тексте, _S_ - количество предложений.
Понятно, что эта оценка ожидаемая (а не гарантированная) из-за наличия хэш-мапы.

### Обработка запросов
* От каждого слова из запроса возьмем все его предложения из `sentencesWithThisWord`.
* Пересчитаем их веса ![alt text](http://mathurl.com/kkk388x.png "Новый вес предложения").
* Выберем _К_ лучших, которые и вернем в качестве результата.
Это _К_ в коде передается вторым параметром в констуктор `SnippetMaker(wifstream &input, int _MAX_SENTENCES_COUNT_FOR_OUTPUT)`.

Это работает за ![alt text](http://mathurl.com/marnlqe.png "Новый вес предложения"),
легко доделывается до ![alt text](http://mathurl.com/k42yeqc.png "Новый вес предложения"), если правильно разбивать запрос на слова.

P.S. тестировалось только на Windows.
