<h3> Лабораторная работа №2 </h3>
Круглова Виктория 22Пи1

Логин, использованный в контесте: vakruglova@edu.hse.ru

<h3>Алгоритм перебора</h3>
brute_alg.cpp

```
void BruteAlg(vector<Rectangle> rectangles, vector<Point> query){
  for (Point po : query) {
    int count = 0;
    for (auto& rec : rectangles) {
      if ((rec.left <= po.x) && (rec.bottom <= po.y) && (rec.right > po.x) && (rec.top > po.y)) {
        count++;
      }
    }
    cout << count << " ";
  }
}
```

<h3>Алгоритм на карте</h3>
map_alg.cpp

```
void MapAlg(vector<Rectangle> rectangles, vector<Point> query) {
	vector<int> x_coord;
	vector<int> y_coord;
	for (Rectangle rec : rectangles){
		x_coord.push_back(rec.left);
		x_coord.push_back(rec.right);
		y_coord.push_back(rec.bottom);
		y_coord.push_back(rec.top);
	}
	sort(x_coord.begin(), x_coord.end());
	sort(y_coord.begin(), y_coord.end());

	int n = x_coord.size();
	vector<vector<int>> map(n, vector<int>(n, 0));
	for (Rectangle rect : rectangles) {
		int x_id1 = find(x_coord, rect.left);
		int x_id2 = find(x_coord, rect.right);
		int y_id1 = find(y_coord, rect.bottom);
		int y_id2 = find(y_coord, rect.top);
		for (int i = x_id1; i < x_id2; i++) {
			for (int j = y_id1; j < y_id2; j++) {
				map[j][i] += 1;
			}
		}
	}

	for (Point po : query) {
		if ((po.x < x_coord[0]) || (po.y < y_coord[0])) {
                        cout << 0 << " ";
			continue;
		}
		if ((po.x >= x_coord[n - 1]) || (po.y >= y_coord[n - 1])) {
			cout << 0 << " ";
			continue;
		}
		int x_ind = bin_find(x_coord, 0, n - 1, po.x);
		int y_ind = bin_find(y_coord, 0, n - 1, po.y);
		int count = map[y_ind][x_ind];
	}
}
```
Функции find и bin_find реализованы в FindFunc.cpp

<h3>Алгоритм на дереве</h3>
tree_alg.cpp

```
void TreeAlg(vector<Rectangle> rectangles, vector<Point> query) {
	vector<int> x_coord;
	vector<int> y_coord;
	for (Rectangle rec : rectangles) {
		x_coord.push_back(rec.left);
		x_coord.push_back(rec.right);
		y_coord.push_back(rec.bottom);
		y_coord.push_back(rec.top);
	}
	sort(x_coord.begin(), x_coord.end());
	sort(y_coord.begin(), y_coord.end());

	int n = x_coord.size();
	vector<Event> events(n);
	for (Rectangle rec : rectangles) {
		events.push_back(Event(find(x_coord, rec.left), find(y_coord, rec.bottom), find(y_coord, rec.top) - 1, 1));
		events.push_back(Event(find(x_coord, rec.right), find(y_coord, rec.bottom), find(y_coord, rec.top) - 1, -1));
	}
	sort(events.begin(), events.end(), Event());

	vector<Node*> ptree(n);
	ptree[0] = BuildTree(0, n - 1);
	int event_ind = 0;
	for (Event e : events) {
		ptree[e.x] = UpdateTree(ptree[event_ind], e.y1, e.y2, e.state);
		event_ind = e.x;
	}

	for (Point po : query) {
		int x_ind = bin_find(x_coord, 0, n - 1, po.x);
		int y_ind = bin_find(y_coord, 0, n - 1, po.y);

		if ((po.x < x_coord[0]) || (po.y < y_coord[0])) {
                        cout << 0 << " ";
			continue;
		}
		if ((po.x > x_coord[n - 1]) || (po.y > y_coord[n - 1])) {
			cout << 0 << " ";
			continue;
		}
		while (ptree[x_ind] == NULL)
			x_ind = x_ind - 1;

		Node* root = ptree[x_ind];
		int count = GetAns(root, y_ind, 0);
		cout << count << " ";
	}
}

Node* BuildTree(int start, int end) {
	if (start == end) {
		Node* node = new Node(start, end);
		return node;
	}

	int mid = (start + end) / 2;
	Node* left = BuildTree(start, mid);
	Node* right = BuildTree(mid + 1, end);

	Node* node = new Node(start, end);
	node->left = left;
	node->right = right;
	return node;
}

Node* UpdateTree(Node* root, int start, int end, int val) {
	if ((start > root->end) || (end < root->start)) {
		return root;
	}
	if ((start <= root->start) && (end >= root->end)) {
		Node* new_root = new Node(root->start, root->end);
		new_root->left = root->left;
		new_root->right = root->right;
		new_root->mod = root->mod + val;
		return new_root;
	}
	Node* new_root = new Node(root->start, root->end);
	new_root->mod = root->mod;
	new_root->left = UpdateTree(root->left, start, end, val);
	new_root->right = UpdateTree(root->right, start, end, val);
	return new_root;
}

int GetAns(Node* root, int y_ind, int count) {
	if (root != NULL) {
		count += root->mod;
		if (root->left != NULL && root->left->start <= y_ind && y_ind <= root->left->end) {
			return GetAns(root->left, y_ind, count);
		}
		else if (root->right != NULL && root->right->start <= y_ind && y_ind <= root->right->end) {
			return GetAns(root->right, y_ind, count);
		}
		else return count;
	}
	return 0;
}
```

<h1>Код запуска тестов</h1>
main.cpp

```
int main(){

	vector<Rectangle> rectangles = {};
	vector<Point> queries = {};
	for (int N = 11; N < pow(2, 10);) {
		for (int i = 1; i < N; i++) {
			rectangles.push_back(Rectangle(10 * i, 10 * i, 10 * (2*N - i), 10 * (2*N - i)));
		}
		for (int j = 0; j < 1000; j++) {
			queries.push_back(Point(powmod(2693 * j, 31, 20 * N), powmod(2693 * j, 31, 20 * N)));
		}

		cout << "Number of rectangles: " << N-1 << " ";
  
		auto start1 = std::chrono::steady_clock::now();
		BruteAlg(rectangles, queries);
		auto finish1 = std::chrono::steady_clock::now();
		auto func_time_1 = std::chrono::duration_cast<std::chrono::microseconds>(finish1 - start1);
		cout << "Brute Alg: " << int(func_time_1.count()) << "\n";
		
		auto start2 = std::chrono::steady_clock::now();
		MapAlg(rectangles, queries);
		auto finish2 = std::chrono::steady_clock::now();
		auto func_time_2 = std::chrono::duration_cast<std::chrono::microseconds>(finish2 - start2);
		cout << "Map Alg: " << int(func_time_2.count()) << "\n";
  
		auto start3 = std::chrono::steady_clock::now();
		TreeAlg(rectangles, queries);
		auto finish3 = std::chrono::steady_clock::now();
		auto func_time_3 = std::chrono::duration_cast<std::chrono::microseconds>(finish3 - start3);
		cout << "Tree Alg: " << int(func_time_3.count()) << "\n";
		
		N += 30;
	}
}

unsigned long int powmod(unsigned long int num, unsigned long int pow, unsigned long int mod)
{
	if (pow == 0)
		return 1;

	if (pow % 2 == 0) {
		long long z = powmod(num, pow / 2, mod);
		return (z * z) % mod;
	}
	else {
		long long z = powmod(num, (pow - 1) / 2, mod);
		return (num * z * z) % mod;
	}
}
```

<h1>Сырые данные</h1>
Находятся в res.xlsx

<h1>Графики</h1>
Общее время работы:

![image](https://github.com/ktoori/Alg_lab_2/assets/152300646/e933a22c-bd2c-4c84-b0d6-e2c321c11f8b)

Подготовка:

![image](https://github.com/ktoori/Alg_lab_2/assets/152300646/be3ad9df-fe9e-4aac-accd-3a568681037d)

Время обработки запросов:

![image](https://github.com/ktoori/Alg_lab_2/assets/152300646/d42c01f0-bf40-4f6d-b8f1-77d8cadfe89a)

<h1>Выводы</h1>
Алгоритм перебором ниболее быстрый по общему времени работы. 

Подготовка алгоритма на карте занимает больше всего времени, из-за чего он проигрывает двум другим по общему времени работы.

Алгоритм на карте на небольших данных обрабатывает запросы немного быстрее алгоритма на дереве, т.к. взятие элемента массива по индексу быстрее, чем проход по дереву. Но когда данных становится слишком много, подготовка алгоритма на карте занимает слишком много времени, поэтому эффективнее использовать алгоритм на дереве.
