#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#define SCREEN_SIZE_X 1500
#define SCREEN_SIZE_Y 800
using namespace std;
bool display_insert; 
bool display_search; 
bool display_delete; 
bool display_insert_algo; 
bool display_search_algo; 
bool display_delete_algo; 
char not_found[] = "Item Not found";
const char text2[] = " A new key is always inserted at the leaf. We start searching for a key from the root until we hit a leaf node. Once a leaf node is found, the new node is added as a child of the leaf node"; 
const char text3[] = " TIME COMPLEXITY OF INSERTION in BEST CASE = O(log n)";
const char text4[] = " TIME COMPLEXITY OF SEARCHING  = O(log n) ";
const char text5[] = " SEARCH MODE";
const char text6[] = " INSERT MODE";
 const char ins_1[] = "IF TREE = NULL ";
 const char ins_2[] = " SET TREE -> DATA = ITEM ";
 const char ins_3[] = "SET TREE -> LEFT = TREE -> RIGHT = NULL";
 const char ins_4[] = "ELSE IF ITEM < TREE->DATA ";
 const char ins_5[] = "Insert(TREE -> LEFT, ITEM) ";
 const char ins_6[] = "ELSE Insert(TREE->RIGHT, ITEM)";
 const char search1[] = "SEARCH(ROOT,ITEM)";
 const char search2[] = "IF ROOT -> DATA = ITEM OR ROOT = NULL";
 const char search3[] = " Return ROOT";
 const char search4[] = " ELSE IF ROOT < ROOT -> DATA";
 const char search5[] = " Return search(ROOT -> LEFT, ITEM)";
 const char search6[] = " ELSE Return search(ROOT -> RIGHT,ITEM)";
 const char delete1[] = "IF TREE = NULL";
 const char delete2[] = "  Write item not found";
 const char delete3[] = " ELSE IF ITEM < TREE -> DATA";
 const char delete4[] = "Delete(TREE->LEFT, ITEM)";
 const char delete5[] = "ELSE IF TREE -> LEFT AND TREE -> RIGHT";
 const char delete6[] = "SET TEMP = findLargestNode(TREE -> LEFT)";
 const char delete7[] = "SET TREE -> DATA = TEMP -> DATA";
 const char delete8[] = "Delete(TREE -> LEFT, TEMP -> DATA)"; 
 const char delete9[] = "ELSE SET TEMP = TREE";
 const char delete10[] = "IF TREE -> LEFT = NULL AND TREE -> RIGHT = NULL";
 const char delete11[] = "SET TREE = NULL";
 const char delete12[] = "ELSE IF TREE -> LEFT != NULL";
 const char delete13[] = "SET TREE = TREE -> LEFT";
 const char delete14[] = "ELSE SET TREE = TREE -> RIGHT";
 const char delete15[] = "SET TREE = TREE -> LEFT";
 const char delete16[] = "FREE TEMP";
 const char deletetext[] = "DELETE MODE ";
 const char algo[] = "ALGORITHM";
 const char deletetext1[] = "we must delete a node from a binary search tree in such a way, that the property of binary search tree doesn't violate.";
 const char deletetext2[] = "Delete function is used to delete the specified node from a binary search tree";
 const char seachresult[] = "Pink node means node travelled and red node means the desired node ";
 const char deletetext3[] = "Time complexity of deletion is : O(h) where h is the height of the tree";
 char insertnumber1[] = "6";
  char insertnumber2[] = "4";
  char insertnumber3[] = "8"; 
enum color { RED, GREEN, BLUE };
struct node {
	int data;
	struct node* left;
	struct node* right;

};
typedef struct node* NODE;

NODE root = NULL;
void display();
void animation2();
void animation();
void draw_square();
void display_text(int& i);
void display_insert_algorithm(int& i);
void display_delete_algorithm(int& i);
void display_search_algorithm(int& i);
void display_searchtext(int& i);
void display_delettext(int& i);
void draw_margin();
float offset = 0.0;
bool box_clicked = false;
int temp_x, temp_y, temp_item;
bool prev_search = false;

int count_digit(int n) {
	return (log10(n) + 1);
}

void to_string(char* s, int num) {
	int r, d;
	d = count_digit(abs(num));
	if (num == 0)
		s[0] = '0';
	if (num < 0) {
		s[0] = '-';
		d++;
	}
	s[d] = '\0';
	num = abs(num);
	while (num != 0) {
		r = num % 10;
		s[--d] = r + '0';
		num /= 10;
	}
}

void display_string(char s[], float x, float y ) {
	glRasterPos2f(x, y);
	for (int i = 0; s[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	glFlush();
}
class binary_search_tree {

private:
	NODE root;
	int root_centre_x, root_centre_y;
	int node_width;
	float line_color[3] = { 0.0,1.0,0.0 };

	NODE get_minimum(NODE temp, NODE* par) {
		if (temp->left == NULL)
			return temp;
		if (temp->right == NULL)
			return temp;
		*par = temp;
		return get_minimum(temp->left, par);

	}
public:


	binary_search_tree() {
		root = NULL;
		root_centre_x = 725;
		root_centre_y = 750;
		node_width = 25;
	}
	void draw_node(int item, int centre_x, int centre_y, bool write_value = true) {
		char data_string[10];
		glBegin(GL_POLYGON);
		glVertex2f(centre_x + node_width, centre_y + node_width);
		glVertex2f(centre_x - node_width, centre_y + node_width);
		glVertex2f(centre_x - node_width, centre_y - node_width);
		glVertex2f(centre_x + node_width, centre_y - node_width);
		glEnd();
		if (write_value) {
			to_string(data_string, item);
			glColor3f(1.0, 1.0, 0.0);
			display_string(data_string, centre_x - 20, centre_y - 5);
		}
	}


	void draw_arrow(int par_x, int par_y, int node_x, int node_y) {
		
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(par_x, par_y - node_width);
		glVertex2f(node_x, node_y + node_width);
		glEnd();
	}
	
	NODE insert(int item) {
		draw_tree();
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		NODE temp, par = NULL, new_node;
		if (root == NULL) {
			root = (NODE)malloc(sizeof(struct node));
			if (root == NULL) {
				printf("There was an error in creating the node\n");
				return NULL;
			}
			root->data = item;
			root->left = root->right = NULL;
			glColor3f(0.0, 0.0, 0.0);
			draw_node(item, node_x, node_y);
			return root;
		}
		temp = root;
		while (temp != NULL) {
			
			par_x = node_x;
			par_y = node_y;
			node_y -= 70;
			par = temp;
			if (item < temp->data) {
				temp = temp->left;
				node_x -=150 ;
			}
			else {
				temp = temp->right;
				node_x += 150 ;
			}
		}
		new_node = (NODE)malloc(sizeof(struct node));
		if (new_node == NULL) {
			cout << ("There was an error in creating the node\n");
			return NULL;
		}
		new_node->data = item;
		new_node->left = new_node->right = NULL;
		if (item < par->data)
			par->left = new_node;
		else
			par->right = new_node;
		glColor3f(0.0, 0.0, 0.0);
		draw_node(item, node_x, node_y);
		draw_arrow(par_x, par_y, node_x, node_y);
		glFlush();
		return root;
	}

	NODE search(int item) {
		draw_tree();
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		NODE temp, par = NULL, new_node;
		if (root == NULL) {
			glColor3f(1.0, 0.0, 0.0);
			
		}
		temp = root;
		while (temp != NULL) {
			par_x = node_x;
			par_y = node_y;
			par = temp;
			if (item == temp->data) {
				prev_search = true;
				temp_x = node_x;
				temp_y = node_y;
				temp_item = item;
				glColor3f(1.0, 0.0, 0.0);
				draw_node(item, node_x, node_y);
				glFlush();
				return temp;
			}
			else if (item < temp->data) {
				glColor3f(1.0, 0.0, 1.0);
				draw_node(item, node_x, node_y);
				glFlush();
				temp = temp->left;
				node_y -= 70;
				node_x -= 150;
			}
			else {
				glColor3f(1.0, 0.0, 1.0);

				draw_node(item, node_x, node_y);
				glFlush();
				temp = temp->right;
				node_y -= 70;
				node_x += 150;
				
				
			}
		}
		glColor3f(1.0, 0.0, 1.0);
		display_string(not_found, 100, 600);
		glFlush();
		return temp;
	}

	NODE remove(int item) {
		bool found = false;
		int num_of_nodes = 1;
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		NODE temp = root, par = root, new_node;
		if (root == NULL) {
			glColor3f(1.0, 0.0, 0.0);
			display_string(not_found, 100, 600);
			return root;
		}
		while (temp != NULL) {
			if (item == temp->data) {
				found = true;
				if (temp == root) {
					if (temp->left == NULL && temp->right == NULL) {
						root = NULL;
						free(temp);
					}
					if (temp->left != NULL || temp->right != NULL) {
						par = temp;
						NODE min_node = get_minimum(temp->right, &par);
						temp->data = min_node->data;
						temp = min_node;
						item = min_node->data;
						continue;
					}
					if (temp->left != NULL) {
						root = temp->left;
						free(temp);
					}
					if (temp->right != NULL) {
						root = temp->right;
						free(temp);
					}
				}
				else if (temp->left == NULL && temp->right == NULL) {
					if (par->left == temp)
						par->left = NULL;
					else
						par->right = NULL;
					free(temp);
				}
				else if (temp->left != NULL && temp->right != NULL) {
					par = temp;
					NODE min_node = get_minimum(temp->right, &par);
					temp->data = min_node->data;
					temp = min_node;
					item = min_node->data;
					continue;
				}

				else {
					if (temp->left != NULL)
						(par->left == temp) ? (par->left = temp->left) : (par->right = temp->left);
					else
						(par->left == temp) ? (par->left = temp->right) : (par->right = temp->right);
					free(temp);
				}
				break;
			}
			par = temp;
			if (item < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (!found) {
			glColor3f(1.0, 0.0, 0.0);
			display_string(not_found, 150, 600);
		}
		else
			draw_tree();
	}
	void pre_order(NODE temp, binary_search_tree temp_tree) {
		if (temp != NULL) {
			temp_tree.insert(temp->data);
			pre_order(temp->left, temp_tree);
			pre_order(temp->right, temp_tree);
		}
	}

	void draw_tree() {
		binary_search_tree temp_tree;
		display();
		pre_order(root, temp_tree);

		
	}
};
binary_search_tree tree;
NODE(binary_search_tree::* operation)(int) = NULL;
class option_box {


private:
	float bottom_corner_x, bottom_corner_y;
	float bc;
	float height, width;
	float color[3];
	char option_name[20];

public:
	option_box() {
		bottom_corner_x = 0;
		bottom_corner_y = 0;
		width = 0;
		height = 0;
		color[RED] = 0.0;
		color[GREEN] = 0.0;
		color[BLUE] = 1.0;
		strcpy_s(option_name, "");
	}

	option_box(const char name[]) {
		bottom_corner_x = 20;
		bottom_corner_y = 475;
		width = 100;
		height = 50;
		color[RED] = 0.0;
		color[GREEN] = 0.0;
		color[BLUE] = 1.0;
		strcpy_s(option_name, name);
	}

	void draw_box() {

		bottom_corner_y -= offset;
		bc = bottom_corner_x;
		glColor3f(color[RED], color[GREEN], color[BLUE]);
		glBegin(GL_QUADS);
		glVertex2f(bottom_corner_x, bottom_corner_y);
		glVertex2f(bottom_corner_x + width, bottom_corner_y);
		glVertex2f(bottom_corner_x + width, bottom_corner_y + height);
		glVertex2f(bottom_corner_x, bottom_corner_y + height);
		glEnd();
		offset += 75.0;
		glColor3f(1.0, 1.0, 0.0);
		display_string(option_name, bottom_corner_x + 10.0, bottom_corner_y + 20.0);
	}

	bool clicked(int x, int y) {
		if (x > bc && x < bc + width)
			if (y > bottom_corner_y && y < bottom_corner_y + height) {
				box_clicked = true;
				return true;
			}
		return false;
	}
};
option_box insert_box, search_box, delete_box, view_algo , exitapp;

void init() {
	glClearColor(1.0, 0.920, 0.816, 0.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SCREEN_SIZE_X, 0.0, SCREEN_SIZE_Y);
}

void displayOptions() {
	option_box insert_box("Insert"), search_box("Search"), delete_box("Delete"), view_algo("Algo")  , exitapp("Exit") ;
	offset = 0.0;
	insert_box.draw_box();
	search_box.draw_box();
	delete_box.draw_box();
	view_algo.draw_box();
	exitapp.draw_box();
	
	

	::insert_box = insert_box;
	::search_box = search_box;
	::delete_box = delete_box;
	::view_algo = view_algo;
	::exitapp = exitapp;
	
}

void display() {
	int i; 
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glutSwapBuffers();
	draw_margin();
	displayOptions();
	draw_square();
	if (display_search) {


		animation2();
	}
	

	
	if (display_insert) {
		animation();
	}

	glFlush();

	glColor3f(0, 0, 1);
	glRasterPos2f(1300,700);
	int len1 = strlen(algo);
	for (i = 0; i < len1; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, algo[i]);
	}
	glFlush();

	if (display_insert) {
		glClearColor(0.5, 0.5, 0.5, 0);
		display_text(i);
	};
	if (display_search) {
		glClearColor(1.0, 0.920, 0.816, 0.);
		display_searchtext(i);
	}

	if (display_delete) {

		display_delettext(i);
	}


	if (display_insert_algo) {
		display_insert_algorithm(i);
	}

	if (display_search_algo) {
	
		display_search_algorithm(i);
	}
	if (display_delete_algo) {

		display_delete_algorithm(i);
	}

}

void animation2()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex2f(125, 780);
	glVertex2f(100, 720);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex2f(80, 720);
	glVertex2f(115, 720);
	glVertex2f(115, 690);
	glVertex2f(80, 690);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex2f(95, 690);
	glVertex2f(70, 630);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(50, 630);
	glVertex2f(85, 630);
	glVertex2f(85, 600);
	glVertex2f(50, 600);
	glEnd();
}

void animation()
{

	
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(65, 780);
	glVertex2f(35,720);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(65, 780);
	glVertex2f(95, 720);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(85, 720);
	glVertex2f(120, 720);
	glVertex2f(120, 690);
	glVertex2f(85, 690);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex2f(20, 720);
	glVertex2f(55, 720);
	glVertex2f(55, 690);
	
	glVertex2f(20,690);
	
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(100,690);
	glVertex2f(100, 630);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(102, 630);
	glVertex2f(78, 655);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(102, 630);
	glVertex2f(121, 655);
	glEnd();

	

	display_string(insertnumber1, 95, 697);
	display_string(insertnumber2, 32, 697);
	display_string(insertnumber3, 95, 605);

	
	

	

}

void draw_square()
{
	glLineWidth(8);
	glColor3f(0,0 , 1);
	glBegin(GL_LINES);
	glVertex2f(40, 140);
	glVertex2f(80, 140);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(80, 140);
	glVertex2f(80, 100);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(80, 100);
	glVertex2f(40, 100);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(40, 100);
	glVertex2f(40, 140);
	glEnd();
	
	
	
	
}

void display_text(int& i)
{
	glColor3f(0, 0, 1);

	glRasterPos2f(149, 150);
	int len1 = strlen(text2);
	for (i = 0; i < len1; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text2[i]);
	}
	glFlush();

	glRasterPos2f(149, 120);
	int len2 = strlen(text3);
	for (i = 0; i < len2; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text3[i]);
	}
	glFlush();
	glRasterPos2f(140, 770);
	int len5 = strlen(text6);
	for (i = 0; i < len5; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text6[i]);
	}
	glFlush();

}

void display_insert_algorithm(int &i)
{
	glRasterPos2f(1220, 625);
	int len6 = strlen(ins_1);
	for (i = 0; i < len6; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ins_1[i]);
	}
	glFlush();
	glRasterPos2f(1220, 605);
	int len7 = strlen(ins_2);
	for (i = 0; i < len7; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ins_2[i]);
	}
	glFlush();
	glRasterPos2f(1220, 585);
	int len8 = strlen(ins_3);
	for (i = 0; i < len8; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ins_3[i]);
	}
	glFlush();

	glRasterPos2f(1220, 565);
	int len9 = strlen(ins_4);
	for (i = 0; i < len9; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ins_4[i]);
	}
	glFlush();
	glRasterPos2f(1220, 545);
	int len10 = strlen(ins_5);
	for (i = 0; i < len10; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ins_5[i]);
	}
	glFlush();


	glRasterPos2f(1220, 525);
	int len11 = strlen(ins_6);
	for (i = 0; i < len11; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ins_6[i]);
	}
	glFlush();


}
void display_delete_algorithm(int& i)
{
	glRasterPos2f(1220, 625);
	int len12 = strlen(delete1);
	for (i = 0; i < len12; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete1[i]);
	}
	glFlush();
	glRasterPos2f(1220, 605);
	int len13 = strlen(delete2);
	for (i = 0; i < len13; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete2[i]);
	}
	glFlush();
	glRasterPos2f(1220, 585);
	int len14 = strlen(delete3);
	for (i = 0; i < len14; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete3[i]);
	}
	glFlush();
	glRasterPos2f(1220, 565);
	int len15 = strlen(delete4);
	for (i = 0; i < len15; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete4[i]);
	}
	glFlush();
	glRasterPos2f(1220, 545);
	int len16 = strlen(delete5);
	for (i = 0; i < len16; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete5[i]);
	}
	glFlush();
	glRasterPos2f(1220, 525);
	int len17 = strlen(delete6);
	for (i = 0; i < len17; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete6[i]);
	}
	glFlush();
	glRasterPos2f(1220, 505);
	int len18 = strlen(delete7);
	for (i = 0; i < len18; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete7[i]);
	}
	glFlush();
	glRasterPos2f(1220, 485);
	int len19 = strlen(delete8);
	for (i = 0; i < len19; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete8[i]);
	}
	glFlush();
	glRasterPos2f(1220, 465);
	int len20 = strlen(delete9);
	for (i = 0; i < len20; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete9[i]);
	}
	glFlush();
	glRasterPos2f(1220, 445);
	int len21 = strlen(delete9);
	for (i = 0; i < len21; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete10[i]);
	}
	glFlush();
	glRasterPos2f(1220, 425);
	int len22 = strlen(delete11);
	for (i = 0; i < len22; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete11[i]);
	}
	glFlush();
	glRasterPos2f(1220, 405);
	int len23 = strlen(delete12);
	for (i = 0; i < len23; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete12[i]);
	}
	glFlush();
	glRasterPos2f(1220, 385);
	int len24 = strlen(delete13);
	for (i = 0; i < len24; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete13[i]);
	}
	glFlush();

	glRasterPos2f(1220, 365);
	int len25 = strlen(delete14);
	for (i = 0; i < len25; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete14[i]);
	}
	glFlush();
	glRasterPos2f(1220,345);
	int len26 = strlen(delete15);
	for (i = 0; i < len26; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete15[i]);
	}
	glFlush();

	glRasterPos2f(1220,325);

	int len27 = strlen(delete16);
	for (i = 0; i < len27; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, delete16[i]);
	}
	glFlush();
}

void display_search_algorithm(int& i)
{

	glRasterPos2f(1220, 605);
	int len12 = strlen(search1);
	for (i = 0; i < len12; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, search1[i]);
	}
	glFlush();
	glRasterPos2f(1220, 585);
	int len13 = strlen(search2);
	for (i = 0; i < len13; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, search2[i]);
	}
	glFlush();
	glRasterPos2f(1220,565);
	int len14 = strlen(search3);
	for (i = 0; i < len14; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, search3[i]);
	}
	glFlush();
	glRasterPos2f(1220, 545);
	int len15 = strlen(search4);
	for (i = 0; i < len15; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, search4[i]);
	}
	glFlush();
	glRasterPos2f(1220, 525);
	int len16 = strlen(search5);
	for (i = 0; i < len16; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, search5[i]);
	}
	glFlush();
	glRasterPos2f(1220, 505);
	int len17 = strlen(search6);
	for (i = 0; i < len17; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, search6[i]);
	}
	glFlush();
}

void display_searchtext(int& i)
{
	glColor3f(0, 0, 1);
	glRasterPos2f(149, 110);
	int len3 = strlen(text4);
	for (i = 0; i < len3; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text4[i]);
	}
	glFlush();
	glColor3f(0, 0, 1);
	glRasterPos2f(149, 150);
	int len6 = strlen(seachresult);
	for (i = 0; i < len6; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, seachresult[i]);
	}
	glFlush();

	glRasterPos2f(140, 770);
	int len4 = strlen(text5);
	for (i = 0; i < len4; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text5[i]);
	}
	glFlush();
	

}

void display_delettext(int& i)
{

	glColor3f(0, 0, 1);
	glRasterPos2f(140, 770);
	int len28 = strlen(deletetext);
	for (i = 0; i < len28; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, deletetext[i]);
	}
	glFlush();

	glColor3f(0, 0, 1);
	glRasterPos2f(149,150);
	int len2 = strlen(deletetext1);
	for (i = 0; i < len2; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, deletetext1[i]);
	}
	glFlush();



	glRasterPos2f(149, 125);
	int len1 = strlen(deletetext2);
	for (i = 0; i < len1; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, deletetext2[i]);
	}
	glFlush();

	glRasterPos2f(149, 100);
	int len6 = strlen(deletetext3);
	for (i = 0; i < len6; i++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, deletetext3[i]);
	}
	glFlush();


}

void draw_margin()
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(8);
	glBegin(GL_LINES);

	glVertex2f(140, 800);
	glVertex2f(140, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(140, 170);
	glVertex2f(1200, 170);
	glEnd();


	glBegin(GL_LINES);   
	glVertex2f(1200, 800);
	glVertex2f(1200, 0);
	glEnd();
}

void mouse(int button, int state, int x, int y) {
	y = SCREEN_SIZE_Y - y;
	tree.draw_tree();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		if (prev_search == true) {
			glColor3f(0.0, 0.0, 0.0);
			tree.draw_node(temp_item, temp_x, temp_y);
			tree.draw_tree();
			prev_search = false;
		}
		if (insert_box.clicked(x, y)) {
			operation = &binary_search_tree::insert;
			glColor3f(1.0, 0.0, 0.0);
			glFlush();
			
			display_insert = true; 
			display_search = false; 
			display_delete = false; 
		}
		if (search_box.clicked(x, y)) {
			operation = &binary_search_tree::search;
			
			glColor3f(1.0, 0.0, 0.0);
			glFlush();
			display_search = true; 
			display_insert = false;
			display_delete = false; 
		}

		if (delete_box.clicked(x, y)) {
			operation = &binary_search_tree::remove;
			
			glColor3f(1.0, 0.0, 0.0);
			display_search = false; 
			display_insert = false; 
			display_delete = true; 

			glFlush();

			tree.draw_tree();
		}

		if (view_algo.clicked(x, y)) {

			int i; 
			if (display_insert) {
				display_insert_algo = true; 
				display_search_algo = false;
				display_delete_algo = false;


			}
			if (display_search) {
				display_insert_algo = false; 
				display_search_algo = true; 
				display_delete_algo = false;
			}

			if (display_delete) {

				display_insert_algo = false; 
				display_search_algo = false; 
				display_delete_algo = true; 
			}


		}

		if (exitapp.clicked(x, y)) {
			exit(0);
		}
	}
}
void keyboard(unsigned char key, int x, int y)
{
	char s[2];
	static int digit = 0;
	static int number = 0;
	static int sign = 1;

	
	if (key != 13 && isdigit(key))
	{
		digit++;
		number = (number * 10) + key - '0';
		s[0] = key;
		s[1] = '\0';
		glColor3f(1.0, 0.0, 0.0);
		display_string(s, 31 + (15 * digit), 115);
		glFlush();
	}
	
	else if (key != 13 && !isdigit(key));
	else {
		digit = 0;
		
		(tree.*operation)(sign * number);
		number = 0;
		sign = 1;
		box_clicked = false;
	}
}

void main(int argc, char** argv) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Binary Search Tree");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	init();

	glutMainLoop();
}
