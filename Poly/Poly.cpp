#include <stdio.h>
#include "Poly.h"
#include <iostream>
#include <cmath>
using namespace std;

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode *CreatePoly(char *expr){		
	return NULL;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	// Fill this in
} // end-DeletePoly
	
//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode *head, double coef, int exp){
	// yeni node'u oluştur
	PolyNode* newNode = new PolyNode;
	newNode->coef = coef;
	newNode->exp = exp;
	newNode->next = NULL;
	// eğer liste boşsa yeni node'u başa ekle ve onu döndür
	if (head == NULL) {
		if (coef == 0) {
			delete newNode;
			return NULL;
		}
		return newNode;
	}
	// eğer yeni node'un üssü baştaki node'un üssünden büyükse, yeni node'u başa ekle
	if(exp > head->exp) {
		newNode->next = head;
		return newNode;
	}
	// eğer üsler eşitse katsayıları topla 0'a özdel durum biçilir.
	if(exp == head->exp){
		double newCoef = head->coef + coef;
		delete newNode; // artık head ile devam edebiliriz
		if(newCoef == 0){
			PolyNode* temp = head->next;
			delete head;
			return temp;// listenin kalanını kaybetmemek için
		}else{
			head->coef = newCoef;// katsayı güncellendi
			return head;
		}
	}
	// liste boş değilse direkt head ile işimiz yoksa listeyi dolaşmamız gerekir iki işaretçiyle listeyi dolaşacağız (prev ve current)
	PolyNode* prev = head;
	PolyNode* current = head->next;

	while(current != NULL){
		if (exp > current->exp){
			// aradığımız yer burası
			break;
		}
		if(exp == current->exp){
			double newCoef = current->coef + coef;
			delete newNode; // artık current ile devam edebiliriz
			if(newCoef == 0){
				prev->next = current->next;
				delete current;	// current node'una artık ihtiyacımız kalmadı
			}else{
				current->coef = newCoef; // katsayı güncellendi
			}
			return head; // head değişmedi
		}
		prev = current;
		current = current->next;		
	}
	// current ya NULL idi ya da en küçük üsse sahipti
	// yeni node'u prev'in sonrasına ekle
	prev->next = newNode;
	newNode->next = current;
	return head;// head değişmedi

} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode *Add(PolyNode *poly1, PolyNode *poly2){
	PolyNode* newHead= NULL;
	PolyNode* p1 = poly1;
	PolyNode* p2 = poly2;
	while (p1 != NULL && p2 != NULL) {
		if(p1->exp > p2->exp){
			newHead = AddNode(newHead, p1->coef, p1->exp);
			p1 = p1->next;
		} else if (p2->exp > p1->exp) {
			newHead = AddNode(newHead, p2->coef, p2->exp);
			p2 = p2->next;
		} else {
			double sumCoef = p1->coef + p2->coef;
			
			newHead = AddNode(newHead, sumCoef, p1->exp);
			
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	while (p1 != NULL) {
		newHead = AddNode(newHead, p1->coef, p1->exp);
		p1 = p1->next;
	}
	while (p2 != NULL) {
		newHead = AddNode(newHead, p2->coef, p2->exp);
		p2 = p2->next;
	}
	return newHead;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode *Subtract(PolyNode *poly1, PolyNode *poly2){
	PolyNode* newHead= NULL;
	PolyNode* p1 = poly1;
	PolyNode* p2 = poly2;
	while (p1 != NULL && p2 != NULL) {
		if(p1->exp > p2->exp){
			newHead = AddNode(newHead, p1->coef, p1->exp);
			p1 = p1->next;
		} else if (p2->exp > p1->exp) {
			newHead = AddNode(newHead, -p2->coef, p2->exp);
			p2 = p2->next;
		} else {
			double sumCoef = p1->coef - p2->coef;
			
			newHead = AddNode(newHead, sumCoef, p1->exp);
			
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	while (p1 != NULL) {
		newHead = AddNode(newHead, p1->coef, p1->exp);
		p1 = p1->next;
	}
	while (p2 != NULL) {
		newHead = AddNode(newHead, -p2->coef, p2->exp);
		p2 = p2->next;
	}
	return newHead;

} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	return NULL;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x){
	double totalSum = 0.0;
	PolyNode* current = poly;
	while(current != NULL){
		double termValue = current->coef * pow(x, current->exp);
		totalSum += termValue;
		current = current->next;
	}
	return totalSum;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode *Derivative(PolyNode *poly){
	PolyNode* derivHead = NULL;
	PolyNode* current = poly;
	while(current != NULL){
		if(current->exp > 0){
			double newCoef= current->coef *current->exp;
			int newExp = current->exp -1;
			derivHead = AddNode(derivHead, newCoef, newExp);
		}
		current = current->next;
	}
	return derivHead;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2){
	
} //end-Plot
