#include <iostream>
#define MAX 20001

using namespace std;

/*--------lista--------*/
struct listNode
{
    char data;                      // znak
    listNode* next;         // wskaznik do nastepnego wezla
    listNode* prev;         // wskaznik do poprzedniego wezla
};

struct list
{
    listNode* head;         // wskaznik na pierwszy wezel listy (najmlodszy)
    listNode* tail;         // wskaznik na ostatni wezel listy (najstarszy)
};

void initializeList(list* l)            // wyzerowanie pustej listy
{
    l->head = nullptr;
    l->tail = nullptr;
}

void addListNode(list* l, char data)             // dodawanie wezla na poczatek listy
{
    listNode* newNode = new listNode;
    newNode->data = data;
    newNode->next = l->head;                                // stary head jest nextem nowego wezla
    newNode->prev = nullptr;

    if (l->head)
    {
        l->head->prev = newNode;                        // stary head dostaje nowy wezel jako prev
    }
    else
    {
        l->tail = newNode;                                      // jesli lista byla pusta, to nowy wezel jest tez ogonem
    }

    l->head = newNode;
}

void addListNodeToEnd(list* l, char data)
{
    listNode* newNode = new listNode;
    newNode->data = data;
    newNode->next = nullptr;                                // nowy wezel bedzie ostatni
    if (l->tail)
    {
        l->tail->next = newNode;                        // stary ogon dostaje nowy next
        newNode->prev = l->tail;                        // nowy wezel dostaje starego ogona jako poprzednika
    }
    else
    {
        l->head = newNode;                                      // jesli lista byla pusta, to nowy wezel jest tez glowa
        newNode->prev = nullptr;
    }

    l->tail = newNode;                                      // nowy wezel jest ogonem listy
}

void freeList(listNode* head)            // zwalnianie pamieci
{
    if (head == nullptr)
    {
        return;
    }
    freeList(head->next);
    delete head;
}

void printList(listNode* head)   // wyswietlanie listy
{
    if (head == nullptr)
    {
        return;
    }
    cout << head->data;             // wypisz zawartosc
    printList(head->next);  // kolejny
}

listNode* copyListsNodes(listNode* n)           // kopiowanie od heada do konca
{
    if (n == nullptr)
    {
        return nullptr;
    }

    listNode* newNode = new listNode;
    newNode->data = n->data;
    newNode->next = copyListsNodes(n->next);

    if (newNode->next)              // jesli ma nexta
    {
        newNode->next->prev = newNode;          // to jego poprzednikiem jest wezel
    }

    newNode->prev = nullptr;
    return newNode;
}

listNode* findTail(listNode* head)      // znajdowanie ostatniego wezla listy na podstawie heada
{
    if (head == nullptr || head->next == nullptr)           // heada nie ma lub head jest tez tailem
    {
        return head;
    }
    return findTail(head->next);            // kolejny
}

list* copyList(list* orig)               // kopiowanie calej listy
{
    if (orig == nullptr || orig->head == nullptr)           // listy nie ma lub jest pusta          
    {
        list* newList = new list;
        newList->head = nullptr;
        newList->tail = nullptr;

        return newList;
    }

    list* newList = new list;
    newList->head = copyListsNodes(orig->head);
    newList->tail = findTail(newList->head);

    return newList;
}

int convertsListToInt(listNode* n, int multiplier)       // konwersja listy na inta
{
    if (n == nullptr)
    {
        return 0;
    }

    if (n->next == nullptr)
    {
        if (n->data == '-')
        {
            return 0;
        }
        return (n->data - '0') * multiplier;
    }
    return (n->data - '0') * multiplier + convertsListToInt(n->next, multiplier * 10);              // reprezentacja dziesietna
}

void saveIntAsList(list* l, int n)      // konwersja inta na liste
{
    if (n == 0)
    {
        if (l->head == nullptr)
        {
            addListNodeToEnd(l, '0');       // dodanie 0 do listy, gdy pusta 'liczba'
        }
        return;
    }

    addListNodeToEnd(l, (n % 10) + '0'); // dodanie ostatniej cyfry do listy
    saveIntAsList(l, n / 10);
}

int finInt(list* l)             // konwersja na int z uwzglednieniem znaku
{
    if (l == nullptr || l->head == nullptr)
    {
        return 0;
    }

    if (l->tail != nullptr && l->tail->data == '-')                 // jesli ostatni wezel to minus
    {
        return -convertsListToInt(l->head, 1);          // konwersja na liczbe ujemna
    }
    else
    {
        return convertsListToInt(l->head, 1);    // konwersja na liczbe dodatnia
    }
}

void removeTailNode(list* l)    // usuwanie ostatniego wezla
{
    if (l->tail == nullptr)
    {
        return;
    }
    listNode* temp = l->tail;       // tymczasowy wskaznik na ogon listy
    l->tail = l->tail->prev;        // przesuniecie ogona listy
    if (l->tail)
    {
        l->tail->next = nullptr;        // jesli nowy ogon jest, jego next na nullptr
    }
    else {
        l->head = nullptr;      // jesli lista stala sie pusta
    }
    delete temp;    // usuniecie wezla
}

void removeHeadNode(list* l)            // usun od glowy wezel
{
    if (l->head == nullptr)
    {
        return;
    }

    listNode* temp = l->head;
    l->head = l->head->next;        // przesuniecie glowy listy
    if (l->head)
    {
        l->head->prev = nullptr;        // jesli nowa glowa jest, jej poprzednik na nullptr
    }
    else
    {
        l->tail = nullptr;      // jesli lista stala sie pusta
    }
    delete temp;
}

bool isNegative(listNode* node)         // wez znak z wezla (taila) i zobacz czy minus
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == '-')
    {
        return true;
    }
    return isNegative(node->next);
}

int nodeCounter(listNode* node)         // liczy wezly
{
    if (node == nullptr)
    {
        return 0;
    }

    if (node->next == nullptr || node->next == node)
    {
        return 1;
    }

    return 1 + nodeCounter(node->next);
}

void deleteNodes(listNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteNodes(node->next);        // usun kolejne wezly

    delete node;    // usun biezacy
}

void deleteNodesAfter(listNode* node)                   // usuwanie wezlow po danym wezle
{
    if (node == nullptr || node->next == nullptr)
    {
        return;
    }

    deleteNodes(node->next);

    node->next = nullptr;
}

listNode* skipUselessZeros(listNode* node)      // zwraca najstarsza niezerowa cyfre
{
    if (!node)
    {
        return nullptr;
    }
    if (node->prev && (node->data == '0' || node->data == '-'))
    {
        return skipUselessZeros(node->prev);
    }
    return node;
}

list* returnListWithoutLeadingZeros(list* l)            // zwraca liste bez wiodacych zer
{
    if (l == nullptr || l->tail == nullptr)
    {
        return nullptr;
    }
    listNode* newTail = skipUselessZeros(l->tail);  // pomijanie zer wiodacych, tailem jest najstarsza niezerowa cyfra
    if (newTail == nullptr)
    {
        freeList(l->head);
        initializeList(l);
        addListNodeToEnd(l, '0');
        return l;
    }

    deleteNodesAfter(newTail);      // usuwanie wezlow po nowym ogonie
    l->tail = newTail;      // ustawienie nowego ogona
    return l;
}

int compareBySingleChar(listNode* a, listNode* b)               // porownywanie po njastarszych znakach
{
    if (a == nullptr && b == nullptr)
    {
        return 0;               // a=b
    }
    if (a->data > b->data)
    {
        return 1;               // a>b
    }
    if (a->data < b->data)
    {
        return -1;              // a<b
    }

    return compareBySingleChar(a->prev, b->prev);

}

int compareCorrect(list* a, list* b)
{
    if (!a || !a->head)
    {
        return (b && b->head) ? -1 : 0;         // jesli a nie ma i: b jest, b>a; jak b tez nie ma a=b 
    }
    if (!b || !b->head)
    {
        return 1;               // a jest b nie ma, wiec a>b
    }

    bool aNeg = isNegative(a->tail);                // sprawdzanie czy liczba jest ujemna
    bool bNeg = isNegative(b->tail);

    a = returnListWithoutLeadingZeros(a);           // wyczyszczone z zer liczby
    b = returnListWithoutLeadingZeros(b);

    int lenA = nodeCounter(a->head);                // okresl liczbe cyfr 
    int lenB = nodeCounter(b->head);


    if (lenA == 1 && a->head && a->head->data == '0')       // dla przypadku '0-' 
    {
        aNeg = false;
    }
    if (lenB == 1 && b->head && b->head->data == '0')
    {
        bNeg = false;
    }

    if (!aNeg && bNeg)              // po znaku +/-
    {
        return 1;               // jesli a dodatnia i b ujemna, wieksza a
    }
    else if (aNeg && !bNeg)
    {
        return -1;              // jesli a ujemna b dodatnia, wieksza b
    }

    if (!aNeg && !bNeg)             // po dlugosci  
    {
        if (lenA > lenB)
        {
            return 1;       // a > b
        }
        else if (lenA < lenB)
        {
            return -1;      // a < b
        }
        else
        {
            return compareBySingleChar(a->tail, b->tail);   // porownanie znak po znaku
        }
    }
    else if (aNeg && bNeg)
    {
        if (lenA > lenB)
        {
            return -1;      // a < b
        }
        else if (lenA < lenB)
        {
            return 1;   // a > b
        }
        else
        {
            return -compareBySingleChar(a->tail, b->tail);          // znak po znaku i przemnozenie -1 bo obie ujemne
        }
    }
    return 0;
}

list* sumCharByChar(listNode* a, listNode* b, int transfer)             // dodawanie pisemne 
{
    if (a && a->data == '-')
    {
        a = nullptr;
    }
    if (b && b->data == '-')
    {
        b = nullptr;
    }

    if (!a && !b && transfer == 0)          // gdy nie ma juz cyfr i transferu to koniec dodawania
    {
        list* res = new list;
        initializeList(res);
        return res;
    }

    int sum = transfer;

    if (a)
    {
        sum += a->data - '0';
    }
    if (b)
    {
        sum += b->data - '0';
    }

    char digit = (sum % 10) + '0';          // liczba jednosci
    transfer = sum / 10;                            // transfer 0 lub 1

    listNode* nextA = (a ? a->next : nullptr);              // jak jest nastepna to daj ja do funkcji jak nie ma to bedzie tam nullptr
    listNode* nextB = (b ? b->next : nullptr);

    list* result = sumCharByChar(nextA, nextB, transfer);
    addListNode(result, digit);

    return result;
}

void borrowMechanism(listNode* a)               // pozyczanie ze starszych cyfr
{
    if (a == nullptr)
    {
        return;
    }
    if (a->data == '0')                     // jak trafisz na zero to zmien na 9
    {
        a->data = '9';
        borrowMechanism(a->next);
    }
    else
    {
        a->data -= 1;   // bo potem i tak bedzie znalezione cos starszego niezerowego, wtedy pozycz
    }
}

list* differenceList(listNode* a, listNode* b)          // odejmowanie pisemne
{
    if (!a && !b)           // obie puste, zwraca pusta liste
    {
        list* res = new list;
        initializeList(res);
        return res;
    }

    int aValue = a ? (a->data - '0') : 0;           // konwersja pojedynczego znaku na int
    int bValue = b ? (b->data - '0') : 0;

    int difference = 0;
    int borrow;

    if (aValue < bValue)
    {
        borrow = 10;            // musi pozyczyc
        borrowMechanism(a->next);                       // mechanizm pozyczania

    }
    else
    {
        borrow = 0;             // nie musi pozyczyc 
    }

    difference = borrow;

    if (a)
    {
        difference += aValue;
    }

    if (b)
    {
        difference -= bValue;
    }

    char digit = (difference % 10) + '0';           // reszta analogicznie jak dodawanie

    listNode* nextA = (a ? a->next : nullptr);
    listNode* nextB = (b ? b->next : nullptr);

    list* result = differenceList(nextA, nextB);
    addListNode(result, digit);

    result = returnListWithoutLeadingZeros(result);

    return result;
}

list* sum(list* a, list* b)             // sumowanie liczb z listy
{
    bool isNegA = isNegative(a->tail);      // sprawdzanie czy liczba jest ujemna
    bool isNegB = isNegative(b->tail);

    list* aListWithoutLeadingZeros = returnListWithoutLeadingZeros(a);      // usuwanie zer wiodacych
    list* bListWithoutLeadingZeros = returnListWithoutLeadingZeros(b);

    if (a->head == nullptr && b->head != nullptr)           //      a nie ma, b jest
    {
        if (isNegB)             // gdy b ujemne
        {
            addListNodeToEnd(bListWithoutLeadingZeros, '-');        // dodanie minusa na koniec listy b
        }
        return b;
    }
    if (b->head == nullptr && a->head != nullptr)           // analogicznie jak wyzej
    {
        if (isNegA)
        {
            addListNodeToEnd(aListWithoutLeadingZeros, '-');
        }
        return a;
    }

    if (!isNegA && !isNegB)                 // jesli obie liczby sa +
    {
        return sumCharByChar(aListWithoutLeadingZeros->head, bListWithoutLeadingZeros->head, NULL);                     // sumowanie liczb
    }
    else if (isNegA && isNegB)
    {
        list* res = sumCharByChar(aListWithoutLeadingZeros->head, bListWithoutLeadingZeros->head, NULL);
        addListNodeToEnd(res, '-');                     // dodanie minusa na koniec listy
        return res;
    }
    else
    {
        int result = compareCorrect(aListWithoutLeadingZeros, bListWithoutLeadingZeros);                 // porownanie liczb
        list* newList = nullptr;
        if (result == 1)                // a > b
        {
            newList = differenceList(aListWithoutLeadingZeros->head, bListWithoutLeadingZeros->head);               // odejmowanie
            if (isNegA)
            {
                addListNodeToEnd(newList, '-');                 // dodanie minusa na koniec listy
            }
        }
        else if (result == -1)                  // b > a
        {
            newList = differenceList(bListWithoutLeadingZeros->head, aListWithoutLeadingZeros->head);               // odejmowanie
            if (isNegB)
            {
                addListNodeToEnd(newList, '-');                 // dodanie minusa na koniec listy
            }
        }
        else
        {
            newList = new list;
            initializeList(newList);
            addListNodeToEnd(newList, '0');                 // dodanie 0 do listy

        }
        return newList;
    }
    return nullptr;
}

/*--------stos--------*/

struct stackNode
{
    list* content;                  // lista
    stackNode* next;        // wskaznik do nastepnego wezla
    stackNode* prev;        // wskaznik do poprzedniego wezla
};

struct stack
{
    stackNode* top;  // wskaznik na szczyt stosu (najmlodszy)
    stackNode* bottom;      // wskaznik na dol stosu (najstarszy)
};

void initializeStack(stack* s)          // pusty stos
{
    s->top = nullptr;
    s->bottom = nullptr;
}

void push(stack* s, list* data)
{
    stackNode* newNode = new stackNode;                     // nowy wezel stosu
    newNode->content = data;                                        // przypisanie listy do wezla
    newNode->next = s->top;                                         // stary top jest nextem nowego wezla
    newNode->prev = nullptr;                                        // nowy wezel nie ma poprzednika

    if (s->top)
    {
        s->top->prev = newNode;         // stary top dostaje poprzednika
    }
    else {
        s->bottom = newNode;            // jesli stos byl pusty, to nowy wezel jest tez dolnym wezlem
    }

    s->top = newNode;       // nowy wezel szczytem stosu
}

list* pop(stack* s)              // zdejmij ze stosu
{
    if (!s->top)            // jesli stos jest pusty
    {
        return nullptr;
    }

    stackNode* temp = s->top;                       // tymczasowy wskaznik na szczyt stosu
    list* data = temp->content;                     // pobranie listy z wezla

    s->top = temp->next;                            // przesuniecie szczytu stosu na dawnego nexta wierzcholka

    if (s->top)
    {
        s->top->prev = nullptr;          // jesli nowy szczyt jest, to jego poprzednik na nullptr
    }
    else
    {
        s->bottom = nullptr;
    }

    delete temp;
    return data;
}

stackNode* getStackNodeByIndex(stackNode* node, int index)              // wskaznik na wezel o danym indexie 
{
    if (node == nullptr || index == 0)
    {
        return node;
    }
    return getStackNodeByIndex(node->next, index - 1);
}

int stackNodesCounter(stackNode* node)          // zwroc miejsce listy na stosie od wierzcholka
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + stackNodesCounter(node->prev);
}

void PrintStack(stackNode* node, int index)             // stos na wyjscie, cala zawartosc
{
    if (node == nullptr)
    {
        return;
    }
    cout << index << ": ";
    printList(node->content->head);
    cout << endl;
    PrintStack(node->prev, index - 1);
}

int main()
{
    char* program = new char[MAX];
    cin >> program;


    stack stos;
    initializeStack(&stos);                 // inicjalizacja stosu

    for (int i = 0; program[i] != '\0'; i++)
    {
        char instruction = program[i];

        switch (instruction) {
        default:
        {
            if (stos.top)
            {
                addListNode(stos.top->content, instruction);    // dodaj do listy
            }
        }
        break;

        case '\'':                              // pusta lista na stos
        {
            list* newList = new list;       // nowa lista
            initializeList(newList);    // inicjalizacja listy
            push(&stos, newList);           // dodaj na stos     
        }
        break;

        case ',':
        {
            list* removedList = pop(&stos);                 // zdejmij liste ze stosu
            if (removedList)                                                 // jesli lista nie jest pusta
            {
                freeList(removedList->head);            // usun wezly   
                delete removedList;                                     // zwolnij pamiec
            }
        }
        break;

        case ':':
        {
            if (stos.top)
            {
                list* copiedList = copyList(stos.top->content);         // skopiuj liste ze szczytu stosu
                push(&stos, copiedList);                                                // dodaj skopiowana liste na stos
            }
        }
        break;

        case ';':
        {
            if (stos.top && stos.top->next)         // jesli istnieja co najmniej dwie listy
            {
                list* temp = stos.top->content;
                stos.top->content = stos.top->next->content;
                stos.top->next->content = temp;                                 // zamiana miejscami dwoch list
            }
        }
        break;

        case '@':
        {
            list* removedList = pop(&stos);                 // zdejmij liste ze stosu
            if (removedList)
            {
                int number = finInt(removedList);       // konwersja listy na liczbe
                freeList(removedList->head);            // usun wezly
                delete removedList;                                     // zwolnij pamiec

                stackNode* aim = getStackNodeByIndex(stos.top, number); // znajdz liste na stosie

                if (aim)
                {
                    list* copiedList = copyList(aim->content);      // skopiuj liste
                    push(&stos, copiedList);        // dodaj skopiowana liste na stos
                }
            }
        }
        break;

        case '&':
        {
            stackNode* current = stos.bottom;               // bierzemy na spodzie, wypisywanie od konca
            int number = stackNodesCounter(current) - 1;
            PrintStack(current, number);    // wyswietl stos
        }
        break;

        case '.':
        {
            char znak;
            cin >> znak;            // pobierz znak
            if (stos.top)
            {
                addListNode(stos.top->content, znak);   // dodaj do listy
            }
        }
        break;

        case '>':
        {
            if (stos.top)
            {
                cout << stos.top->content->head->data;  // wyswietl pierwszy element listy z wierzcholka stosu
                list* removedList = pop(&stos);                 // zdejmij liste ze stosu
                if (removedList)                                // jesli lista nie jest pusta 
                {
                    freeList(removedList->head);            // usun wezly   
                    delete removedList;                                     // zwolnij pamiec
                }
            }
        }
        break;

        case '-':
        {
            if (stos.top && stos.top->content)
            {
                list* currentList = stos.top->content;
                if (currentList->tail && currentList->tail->data == '-')
                {
                    removeTailNode(currentList);  // usuniecie ostatniego elementu
                }
                else
                {
                    addListNodeToEnd(currentList, '-');  // dodaj minus na koniec listy
                }
            }
        }
        break;

        case '^':
        {
            if (stos.top && stos.top->content)
            {
                list* currentList = stos.top->content;                                          // zawartosc listy na wierzcholku
                if (currentList->tail && currentList->tail->data == '-')                // jesli ostatni znak listy minus
                {
                    removeTailNode(currentList);            // to usun
                }
            }
        }
        break;

        case ']':
        {
            list* removedList = pop(&stos);                 // zdejmij liste ze stosu
            if (removedList)
            {
                int number = finInt(removedList);  // konwersja listy na liczbe
                char asciiByInt = number;
                freeList(removedList->head);            // usun wezly
                delete removedList;                             // zwolnij pamiec

                list* newList = new list;                       // nowa lista
                initializeList(newList);                        // inicjalizacja listy
                addListNode(newList, asciiByInt);               // dodaj znak do listy
                push(&stos, newList);                           // dodaj na stos
            }
        }
        break;

        case '[':
        {
            list* removedList = pop(&stos);                 // zdejmij liste ze stosu
            if (removedList && removedList->head)
            {
                int firstCharInList = removedList->head->data;          // pierwszy znak w liscie
                freeList(removedList->head);
                delete removedList;

                list* newList = new list;
                initializeList(newList);
                saveIntAsList(newList, (int)firstCharInList);                   // dodaj liczbe do listy
                push(&stos, newList);
            }

        }
        break;

        case '$':
        {
            if (stos.top && stos.top->content)
            {
                list* currentList = stos.top->content;
                char firstChar = currentList->head->data;       // pierwszy znak w liscie
                if (currentList->head)
                {
                    removeHeadNode(currentList);  // usuniecie pierwszego elementu
                }

                list* newList = new list;
                initializeList(newList);
                addListNode(newList, firstChar);        // dodaj znak do listy
                push(&stos, newList);
            }
        }
        break;

        case '#':
        {
            list* removedList = pop(&stos);          // zdejmij liste ze stosu
            if (removedList && removedList->head && stos.top && stos.top->content)
            {
                if (stos.top->content->head == nullptr)
                {
                    stos.top->content->head = removedList->head;
                    stos.top->content->tail = removedList->tail;
                }
                else
                {
                    stos.top->content->tail->next = removedList->head;              // ostatni wezel nowej listy wskazuje na pierwszy element usunietej listy
                    removedList->head->prev = stos.top->content->tail;              // pierwszy element usunietej listy wskazuje na ostatni element nowej listy
                    stos.top->content->tail = removedList->tail;            // ogon nowej listy wskazuje na ogon usunietej listy
                }

                removedList->head = nullptr;
                removedList->tail = nullptr;

                delete removedList;     // zwolnij pamiec
            }
        }
        break;

        case '<':
        {
            list* removedListA = pop(&stos);                // sciagam dwie listy
            list* removedListB = pop(&stos);

            list* newList = new list;
            initializeList(newList);
            int result = compareCorrect(removedListA, removedListB);                // porownanie 
            if (result == 1)
            {
                addListNode(newList, '1');
            }
            else
            {
                addListNode(newList, '0');
            }

            push(&stos, newList);
        }
        break;

        case '=':
        {
            list* removedListA = pop(&stos);                // sciagamy
            list* removedListB = pop(&stos);

            list* newList = new list;
            initializeList(newList);
            int result = compareCorrect(removedListA, removedListB);                // porownanie
            if (result == 0)
            {
                addListNode(newList, '1');
            }
            else
            {
                addListNode(newList, '0');
            }
            push(&stos, newList);
        }
        break;

        case '!':
        {
            list* removedList = pop(&stos);
            list* newList = new list;
            initializeList(newList);
            if (removedList->head == nullptr || (removedList->head->data == '0' && removedList->head->next == nullptr))             // jesli pusta lub tylko zero
            {
                addListNode(newList, '1');
            }
            else
            {
                addListNode(newList, '0');
            }
            push(&stos, newList);
            freeList(removedList->head);
            delete removedList;
        }
        break;

        case '~':
        {
            int instructionNumber = i;
            list* pointerValue = new list;
            initializeList(pointerValue);
            saveIntAsList(pointerValue, instructionNumber);                 // dodaj liczbe do listy
            push(&stos, pointerValue);
        }
        break;

        case '?':
        {
            list* removedListT = pop(&stos);
            list* removedListW = pop(&stos);

            if (!removedListT || !removedListW || !removedListW->head)
            {
                break;
            }

            listNode* wAfterSkip = skipUselessZeros(removedListW->head);                    // pomijanie zer wiodacych

            if (wAfterSkip != nullptr && wAfterSkip->data != '0' && removedListW->head != nullptr)
            {
                i = finInt(removedListT) - 1;                   // ustawienie wskaznika na odpowiednia instrukcje
                break;
            }
        }
        break;

        case '+':
        {
            list* a = pop(&stos);
            list* b = pop(&stos);

            list* newList = sum(a, b);

            push(&stos, newList);

            freeList(a->head);
            delete a;
            freeList(b->head);
            delete b;
        }
        break;
        }
    }

    delete[] program;
}