#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class HuffmanCode {
	string text;
	struct Node {
		char ch; // символ
		int freq;  // частота появления
		Node* left, * right; // левый и правый узлы
	};

public:
	HuffmanCode(string ntext) {
		text = ntext;
	}

	Node* getNode(char ch, int freq, Node* left, Node* right) { // получаем новый узел
		Node* node = new Node();
		node->ch = ch;
		node->freq = freq;
		node->left = left;
		node->right = right;

		return node;
	}

	void encoding(Node* root, string str, unordered_map<char, string> huffmancode) { // кодируем символы строки
		if (root == nullptr) {
			return;
		}
		if (!root->left && !root->right) {
			huffmancode[root->ch] = str;
		}
		encoding(root->left, str + '0', huffmancode);
		encoding(root->right, str + '1', huffmancode);
	}

	void decoding(Node* root, int& id, string str) {  // раскодировка символа
		if (root == nullptr) {
			return;
		}

		if (!root->left && !root->right) {
			cout << root->ch;
			return;
		}

		id++;

		if (str[id] == '0') {
			decoding(root->left, id, str);
		}
		else {
			decoding(root->right, id, str);
		}
	}

        bool comp(Node* l, Node* r) { // компаратор для сортировки по возрастанию
		return l->freq > r->freq;
	}

	void HuffmanTree() {
		unordered_map<char, int> freq;
		for (char ch : text) { // подсчитываем частоту появления каждого символа
			freq[ch]++;
		}

		priority_queue<Node*, vector<Node*>, comp> pq; // создаем приоритетную очередь для храния узлов

		for (auto& pair : freq) {
			pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); // создаем узлы для каждого символа и добваляем в очередь
		}

		while (pq.size() != 1) {                 // извлекаем узлы из очереди
			Node* left = pq.top(); pq.pop();
			Node* right = pq.top();	pq.pop();

			int sum = left->freq + right->freq;
			pq.push(getNode('\0', sum, left, right)); // создаем узел предок с частотой равной сумме частот потомков
		}

		Node* root = pq.top();                   // извлекаем корневой узел
		unordered_map<char, string> huffmanCode;  // контейнер для хранения кода каждого символа
		encoding(root, "", huffmanCode);          // кодируем символы

		cout << "Huffman Codes are : " << endl;  // выводим коды символов
		for (auto& pair : huffmanCode) {
			cout << pair.first << " " << freq[pair.first] << " " << pair.second << endl;
		}

		cout << "Original string was : " << text << endl;  
		// выводим изначальную строку
		string str = "";
		for (char ch : text) {
			str += huffmanCode[ch];
		}

		cout << "Encoded string is : " << str << endl;  
		// выводим раскодированную строку
		int id = -1;
		cout << "Decoded string is: " << endl;
		while (id < (int)str.size() - 2) {
			decoding(root, id, str);
		}
	}
};

int main()
{
	HuffmanCode text("The best in St. Petersburg State University - faculty of PM-PU.");

	text.HuffmanTree();

	return 0;
}
