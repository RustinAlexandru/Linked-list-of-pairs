#include "stdafx.h"
#include <iostream>
#include <conio.h>


using namespace std;

int x;

//template <class T>
//class listapereche<T>;

template <class U>
class pereche
{
	template <class U> friend class listapereche;
private:
	U first;
	U last;

public:

	pereche(int _first=0, int _last=0) : first(_first), last(_last){};
	
	template <class U>
	friend istream& operator>>(istream &, pereche<U>&);
	
	template <class U>
	friend ostream& operator<<(ostream &, pereche<U>&);

	template <class U>
	friend ostream& operator<<(ostream &os, listapereche<U> &lp);
	
	friend void listapereche<U>::inserare(U x, U y);
	
	friend void listapereche<U>::afisare();
	
	U getfirst() const
	{
		return first;
	}
	
	U getlast() const { 
		return last;
	}
	
	void setfirst( U _first)
	{
		U first = _first;
	}

	void setlast (U _last){
		U last=_last;
	}
};

template <class U>
istream& operator>>(istream &is, pereche<U> &p)
{
	is >> p.first >> p.last;
	return is;
}

template <class U>
ostream& operator<<(ostream &os, pereche<U> &p)
{
	os << p.first << " " << p.last;
	return os;
}

template <class t>
class LinkedList
{
	 friend class listapereche<t>;
	struct nod
	{
		t info;
		nod *urm;
	} *cap;

public:

	LinkedList()
	{
		cap = new nod;
		cap = NULL;
	};
	~LinkedList();
	LinkedList(const LinkedList<t> &);
	LinkedList<t> operator+ (LinkedList<t>);
	LinkedList<t> operator-(LinkedList<t>);
	LinkedList<t> operator*(LinkedList<t>);
	LinkedList<t> operator=(LinkedList<t>);

	template <class t>
	friend istream& operator>>(istream &, LinkedList<t>&);

	template <class t>
	friend ostream& operator<<(ostream &, LinkedList<t>&);

	void duplicate();


	void reuniune(LinkedList<t>, LinkedList<t>);
	void intersectie(LinkedList<t>, LinkedList<t>);
	void diferenta(LinkedList<t>, LinkedList<t>);
	void inserare(t);
	void afisare();
	void sortare();
	int  gasit(t);
};

template<class t>
LinkedList<t> LinkedList<t>::operator=(LinkedList<t> lista)

{
	cap = NULL;
	nod *q;
	q = lista.cap;
	while (q)
	{
		(*this).inserare(q->info);
		q = q->urm;

	}
	return *this;


}

template <class t>
LinkedList<t>::LinkedList(const LinkedList<t> &lista)
{

	//this->cap = new nod;
	//this->cap->info = lista.cap->info;
	//this->cap->urm = NULL;
	cap = NULL;
	nod *q;
	q = lista.cap;
	while (q)
	{
		(*this).inserare(q->info);
		q = q->urm;

	}

}

template <class t>
LinkedList<t>::~LinkedList()
{

	nod *q, *p;
	p = cap;
	while (p != NULL)
	{
		q = p->urm;
		delete p;
		p = q;
	}
	cap = NULL;
	cout << endl;
	//cout << "destructed";
	cout << endl;
}

template <class t>
istream& operator>>(istream &is, LinkedList<t> &l)
{
	t t;
	char s;
	cout << "c=continue/s=stop" << endl;
	cout << "Forma inserare: numar simbol ( ex 1c 2c 3s)" << endl;

	while (1)
	{

		try{


			is >> t;
			if (!is) throw 10;
			l.inserare(t);

			is >> s;
			if (s == 's') break;
		}
		catch (int)
		{
			cout << "Nu ati introdus corect!";
			x = 9;
			break;
			//exit(0);
		}
	}


	return is;
}

template<class t>
ostream& operator<<(ostream &os, LinkedList<t> &l)
{
	LinkedList<t>::nod *q;
	q = l.cap;
	while (q)
	{
		os << q->info << " ";
		q = q->urm;
	}
	return os;

}

template <class t>
LinkedList<t> LinkedList<t>::operator*(LinkedList<t> l1) // operator inmultire
{
	nod *p1;
	LinkedList<t> rezultat;
	p1 = cap;
	if (!p1 || !l1.cap) rezultat.inserare(0);
	while (p1) // parcurg lista 1
	{
		if (l1.gasit(p1->info)) rezultat.inserare(p1->info); // daca il gasesc in lista2, il adaug in lista rezultat
		p1 = p1->urm;
	}
	return rezultat;
}

template <class t>
LinkedList<t> LinkedList<t>::operator+(LinkedList<t> l1) // operator reuniune
{
	nod *p1, *p2;
	LinkedList<t> rezultat;
	p1 = cap;
	while (p1)  // parcurg lista cu p1
	{
		rezultat.inserare(p1->info); // inserez in lista rezultat tot ce e in lista1
		p1 = p1->urm;
	}
	p2 = l1.cap;
	while (p2) // parcurg lista2
	{
		if (!gasit(p2->info)) rezultat.inserare(p2->info);  //daca nu gasesc nodul din lista2 in lista1, il adaug in lista rezultat
		p2 = p2->urm;
	}
	return rezultat;
}

template<class t>
LinkedList<t> LinkedList<t>::operator-(LinkedList<t> l1) // operator diferenta
{
	nod *p1 = cap;
	LinkedList<t> rezultat;
	while (p1) // parcurg lista 1
	{
		if (l1.gasit(p1->info)) // daca gasesc nodul din lista 1 in lista 2, merg mai departe
			p1 = p1->urm;
		else
		{
			rezultat.inserare(p1->info); // altfel, il inserez in lista rezultat si merg mai departe
			p1 = p1->urm;
		}
	}
	return rezultat;
}

template <class t>
void LinkedList<t>::duplicate()
{
	nod *p1, *p2, *duplicat;
	p1 = cap;
	while (p1 && p1->urm != NULL) // parcurg lista cu p1
	{
		p2 = p1;
		while (p2->urm != NULL) // parcurg lista cu p2
		{
			if (p1->info == p2->urm->info) // daca un element se regaseste din nou, il sterg
			{
				duplicat = p2->urm;     // nod de stergere
				p2->urm = p2->urm->urm; // stergere
				delete[]duplicat;
			}
			else
			{
				p2 = p2->urm;
			}
		}
		p1 = p1->urm;
	}
}

template <class t>
int LinkedList<t>::gasit(t x)
{
	nod *p = cap;
	while (p)           // parcurg lista, caut pe x, daca il gasesc returnez 0
	{
		if (p->info == x) return 1;
		p = p->urm;
	}
	return 0;
}

template <class t>
void LinkedList<t>::reuniune(LinkedList<t> l1, LinkedList<t> l2)
{
	nod *p1, *p2;
	p1 = l1.cap;
	while (p1)  // parcurg lista cu p1
	{
		inserare(p1->info); // inserez in lista rezultat tot ce e in lista1
		p1 = p1->urm;
	}
	p2 = l2.cap;
	while (p2) // parcurg lista2
	{
		if (!l1.gasit(p2->info)) inserare(p2->info);  //daca nu gasesc nodul din lista2 in lista1, il adaug in lista rezultat
		p2 = p2->urm;
	}

}



template <class t>
void LinkedList<t>::intersectie(LinkedList<t> l1, LinkedList<t> l2)
{
	nod *p1;
	p1 = l1.cap;
	if (!p1 || !l2.cap) inserare(0);

	while (p1) // parcurg lista 1
	{
		if (l2.gasit(p1->info)) inserare(p1->info); // daca il gasesc in lista2, il adaug in lista rezultat
		p1 = p1->urm;
	}
}



template <class t>
void LinkedList<t>::diferenta(LinkedList<t> l1, LinkedList<t> l2)
{
	nod *p1 = l1.cap;
	while (p1) // parcurg lista 1
	{
		if (l2.gasit(p1->info)) // daca gasesc nodul din lista 1 in lista 2, merg mai departe
			p1 = p1->urm;
		else
		{
			inserare(p1->info); // altfel, il inserez in lista rezultat si merg mai departe
			p1 = p1->urm;
		}
	}
}


template <class t>
void LinkedList<t>::inserare(t x)
{
	nod *q, *temp;
	q = new nod;
	q->info = x;
	q->urm = NULL;
	if (cap == NULL)  // daca lista e goala, nod nou
	{
		cap = q;
	}
	else
	{
		temp = cap;
		while (temp->urm != NULL)  // parcurg lista, adaug nodul la sfarsit
		{
			temp = temp->urm;
		}
		temp->urm = q;

	}
}

template <class t>
void LinkedList<t>::afisare()
{
	nod *p;
	p = cap;
	while (p)
	{
		cout << p->info << " ";
		p = p->urm;
	}
}

template <class t>
void LinkedList<t>::sortare()
{
	nod *q, *p, *ultim;
	t tmp;

	p = cap;

	while (p)
	{
		p = p->urm;
	}
	ultim = p;

	for (p = cap; p->urm != ultim; p = p->urm)
	{
		for (q = p->urm; q != NULL; q = q->urm)
		if (p->info > q->info)
		{
			tmp = q->info;
			q->info = p->info;
			p->info = tmp;
		}
	}
}

template<class T>
class listapereche
{

	struct node
	{
		pereche<T> pair;
		node *urm;

	} *head;

public:
	template <class T>
	friend istream& operator>>(istream &is, listapereche<T> &lp);
	template <class T>
	friend ostream& operator<<(ostream &os, listapereche<T> &lp);
	
	void produs(LinkedList<T>, LinkedList<T>);
	
	listapereche()	{ head = new node; head = NULL; }
	
	void inserare(T x, T y);
	
	void afisare();

	virtual void test() { cout << "Varianta din baza"; }

};

template <class T>
istream& operator>>(istream &is, listapereche<T> &lp)
{
	T t, z;
	char s;
	cout << "c=continue/s=stop" << endl;
	cout << "Forma inserare: numar numar simbol ( ex: 1 2 c, 2 3 c, 0 0 s)" << endl;

	while (1)
	{

		try{


			is >> t;
			if (!is) throw 10;
			is >> z;
			if (!is) throw 11;
			lp.inserare(t, z);
			is >> s;
			if (s == 's') break;
		}
		catch (int)
		{
			cout << "Nu ati introdus corect!";
			x = 9;
			break;
			//x = 9;
			//exit(0);
		}
	}
	return is;
}

template <class T>
ostream& operator<<(ostream &os, listapereche<T> &lp)
{
	listapereche<T>::node *q = lp.head;

	while (q)
	{
		os << q->pair.first << " " << q->pair.last << endl;
		q = q->urm;
	}
	return os;
}

template <class T>
void listapereche<T>::produs(LinkedList<T> l1, LinkedList<T> l2)
{
	LinkedList<T>::nod *p1, *p2;
	p1 = l1.cap;
	p2 = l2.cap;
	while (p1)
	{
		p2 = l2.cap;
		while (p2)
		{
			inserare(p1->info, p2->info);
			p2 = p2->urm;
		}

		p1 = p1->urm;
	}

}
template <class T>
void listapereche<T>::afisare()
{
	node *p;
	p = head;
	while (p)
	{
		cout << p->pair.first << " " << p->pair.last << endl;
		p = p->urm;
	}
}

template <class T>
void listapereche<T>::inserare(T x, T y)
{
	node *q, *temp;
	q = new node;
	q->pair.first = x;
	q->pair.last = y;
	q->urm = NULL;


	if (head == NULL)  // daca lista e goala, nod nou
	{
		head = q;
	}
	else
	{
		temp = head;
		while (temp->urm != NULL)  // parcurg lista, adaug nodul la sfarsit
		{
			temp = temp->urm;
		}
		temp->urm = q;

	}

	

}
int const size = 100;

template <class T>
class stiva_perechi : public pereche<T>
{
public:	pereche<T> stack[size];
		int tos;
public:
	stiva_perechi(int _tos = -1) :pereche(), tos(_tos) {};
	
	void push(T first, T last)
	{
		if (tos >= 100) cout << "Overflow";
		tos++;
		stack[tos].setfirst(first);
		stack[tos].setlast(last);
	};

	void pop()
	{
		if (tos == -1) cout << "Empty stack";
		cout<<stack[tos].getfirst();
		cout<<stack[tos].getlast();
		tos--;
	}

	bool isEmpty()
	{
		if (top == -1) return 1;
		return 0;
	}

};
template <class T>
class stiva_pereche: public listapereche<T>
{
public:	listapereche<T> stack[size];
		int top;

public:
	
	stiva_pereche(int _top = -1) : listapereche(), top(_top) {};
	
	~stiva_pereche() { }
	
	 void test()
	{
		cout << "Test virtual function:";

	}


	void push(T a, T b) 
	{
		if (top >= 100) cout << "Overflow";
		top++;
		stack[top].inserare(a,b);
	};

	T pop()
	{
		if (top == -1) cout << "Empty stack";
		return stack[top--];
	}

	bool isEmpty()
	{
		if (top == -1) return 1;
		return 0;
	}
};


int main()
{
	LinkedList<char> liste[100];
	listapereche<char> lper[100];


	listapereche<int> *pbaza_stiva,baza_stiva;
	stiva_pereche<int> *pstivap,stivap;
	pbaza_stiva = &stivap;
	pstivap = &stivap;

	listapereche<int> *pbaza_stiva2 = dynamic_cast<listapereche<int>*>(pstivap);
	if (pbaza_stiva2) cout << "gg";

	//stivap->push(2, 2);
	//stivap->stack[0].inserare(3, 3);
	pbaza_stiva->afisare();
	pbaza_stiva->test();
	


	stiva_perechi<int> stiva;
	stiva.push(5, 5);
	stiva.push(6, 6);
	//stiva.pop();
	cout << "Meniu" << endl;
	cout << "Listele sunt numerotate de la 1 la 100" << endl;
	cout << "1. Inserare in  lista i" << endl;
	cout << "2.Afisare lista i" << endl;
	cout << "3.Reuniunea listelor" << endl;
	cout << "4.Intersectia listelor" << endl;
	cout << "5.Diferenta listelor" << endl;
	cout << "6.Inserare in lista pereche i" << endl;
	cout << "7.Afisarea listei pereche i" << endl;
	cout << "8.Produs cartezian liste" << endl;
	cout << "9.Exit" << endl;
	cin >> x;

	do
	{

		switch (x)
		{

		case 1:
			int a;
			cout << "Lista numarul i. Dati i:";
			cin >> a;
			cout << endl;
			cin >> liste[a];

			cout << endl;
			break;

		case 2:
			cout << endl;
			cout << "Dati numarul i al listei ce se doreste afisata:";
			int b;
			cin >> b;
			cout << endl;
			cout << liste[b] << endl;

			break;

		case 3:
			cout << "Dati numerele listelor ce se doresc reunite si unde sa se salveze rezultatul" << endl;
			int l1, l2, lr;
			cin >> l1 >> l2 >> lr;
			liste[lr].reuniune(liste[l1], liste[l2]);
			cout << endl;

			break;
		case 4:
			cout << "Dati numerele listelor ce se doresc intersectate si unde sa se salveze rezultatul" << endl;
			int l3, l4, lre;
			cin >> l3 >> l4 >> lre;
			liste[lre].intersectie(liste[l3], liste[l4]);
			cout << endl;

			break;
		case 5:
			cout << "Dati numerele listelor ce se doresc scazute (diferenta) si unde sa se salveze rezultatul" << endl;
			int l5, l6, lrez;
			cin >> l5 >> l6 >> lrez;
			liste[lrez].diferenta(liste[l5], liste[l6]);
			cout << endl;

			break;
		case 6:
			int c;
			cout << "Lista numarul i. Dati i:";
			cin >> c;
			cout << endl;
			cin >> lper[c];
			cout << endl;

			break;
		case 7:
			cout << "Dati numarul i al listei pereche ce se doreste afisata:";
			int d;
			cin >> d;
			cout << lper[d] << endl;

			break;
		case 9:
			return 0;
		case 8:
			cout << "Dati numerele listelor ce compun produsul cartezian si unde sa se salveze rezultatul" << endl;
			int lp1, lp2, lpr;
			cin >> lp1 >> lp2 >> lpr;
			//lper[lpr].produs(liste[lp1], liste[lp2]);
			cout << endl;
			break;
		default:
			break;

		}
		cout << "Meniu" << endl;
		cout << "Listele sunt numerotate de la 1 la 100" << endl;
		cout << "1. Inserare in  lista i" << endl;
		cout << "2.Afisare lista i" << endl;
		cout << "3.Reuniunea listelor" << endl;
		cout << "4.Intersectia listelor" << endl;
		cout << "5.Diferenta listelor" << endl;
		cout << "6.Inserare in lista pereche i" << endl;
		cout << "7.Afisarea listei pereche i" << endl;
		cout << "8.Produs cartezian liste" << endl;
		cout << "9.Exit" << endl;
		cin >> x;
	} while (x != 0);
	system("pause");
	return 0;
}





