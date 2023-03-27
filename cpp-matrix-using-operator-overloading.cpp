#include<iostream> 
#include<string>
#include<conio.h>
#include<cassert>
#include<Windows.h>
#include <time.h>
#define END 79
#define ESCAPE 27
using namespace std;
class CMatrix {
protected:
	int size;
	int rows, columns;
	int mat[3][3];
public:;
	CMatrix() {// default contructor
		rows = columns = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat[i][j] = 0;
			}
		}
	}  
	CMatrix(const int* r, const int* c) {//parametarized
		rows = *r;
		columns = *c;
		assert("This is like 1d array", rows > 1 || columns > 1);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				mat[i][j] = 0;
		}
	}
	// to set rows and colouns
	void setRowsColumns(const int* r, const int* c) {
		rows = *r, columns = *c;
		assert("This is like 1d array",rows > 1 || columns > 1);
	}

	//input matrix values
	void inputMatrix() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << "  Enter row[" << i<<"]["<< j<< "] : ";
				cin >> mat[i][j];
			}
		}
	}
	 void displayMatrix() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << "\t " << mat[i][j];
			}cout <<"\n\n";
		}
	}
	void enterRC() {//to enter rows an columns
		cout << "\nEnter the rows size of matrix : ";
		cin >> rows;
		cout << "Enter the column size of matrix : ";
		cin >> columns;
		assert(rows > 1 || columns > 1);
	}

	bool operator!() {
		int det;
		det = determinant(mat, rows);
		if (det != 0)
			return true;
		else
			return false;
	}//! body end

	CMatrix& operator +(CMatrix& p)
	{

		CMatrix result(&rows, &columns);
		if (rows == p.rows && columns == p.columns) {//checking order of matrices
			cout << "\nThe matrices are confirmable for addition.\n";
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					result.mat[i][j] = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					result.mat[i][j] = this->mat[i][j] + p.mat[i][j];
				}
			}
		}
		else {
			cout << "\nThe matrices are not confirmable for addition.\n";
			cout << "\t due to different order\n";
		}
		return result;
	}//operator+ body closed

	CMatrix& operator-(CMatrix& other) {

		CMatrix result(&rows, &columns);
		cout << "\nThe matrices are confirmable for addition.\n";
		if (rows == other.rows && columns == other.columns) {//checking order of matrices
			cout << "\nThe matrices are confirmable for subtraction.\n";
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					result.mat[i][j] = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					result.mat[i][j] = other.mat[i][j] - this->mat[i][j];
				}
			}
		}
		else {
			cout << "\nThe matrices are not confirmable for subtraction.\n";
			cout << "\t due to different order\n";
		}
		return result;
	}//- operator body clsed
	CMatrix& operator *(CMatrix& m) {
		int sum, i = 0, j = 0, k = 0;
		//Reulst of multiplication is the rows of 1st and cols of 2nd mat
		CMatrix C(&rows, &m.columns);
		if (columns == m.rows) {//checking order of matrices
			cout << "The matrices are confirmable for multiplication.\n";
			//mult formula
			for (i = 0; i < rows; i++)
			{
				for (j = 0; j < m.columns; j++)
				{
					sum = 0;
					for (k = 0; k < columns; k++) {
						sum = sum + mat[i][k] * m.mat[k][j];
						C.mat[i][j] = sum;
					}
				}//inner for end
			}//outer for end
		}//if body end
		else {
			cout << "\nError! column of first matrix not equal to rows of second"
				<< ".\n";
		}
		return C;
	}//* operator body closed

	CMatrix operator/(int& number) {
		cout << "\n";
		CMatrix res(&rows, &columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				res.mat[i][j] = mat[i][j] / number;
			}
		}
		cout << "1(A)is\n-\n" << number << endl << " \n";
		return res;
	}
	CMatrix operator=(int) {
		CMatrix new_matrix(&rows, &columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				new_matrix.mat[i][j] =mat[i][j];
			}
		}
		return new_matrix;
	}
	bool operator==(CMatrix& other) {
		//checking
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (mat[i][j] != other.mat[i][j])
					return false;
			}
		}

	return true;
	}//==  body end
	int operator()(int r,int c) {
		return mat[r][c];
	}
	CMatrix adjointOfMatrix(int s) {
		int temp;
		if(s==2)
		{
		rows=columns= 2;
		CMatrix res1(&rows, &columns);
		temp = mat[0][0];
		mat[0][0] = mat[1][1];
		mat[1][1] = temp;
		mat[0][1] = -mat[0][1];
		mat[1][0] = -mat[1][0];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				res1.mat[i][j] = mat[i][j];
			}cout << endl;
		}
		return res1;
		}
		else if(s==3)
	    {
			rows =columns = 3;
			CMatrix res(&rows, &columns);
			// Finding cofactor of each
			mat[0][0] = ((mat[1][1] * mat[2][2]) - (mat[1][2] * mat[2][1]));
			mat[0][1] = -((mat[1][0] * mat[2][2]) - (mat[2][0] * mat[1][2]));
			mat[0][2] = (mat[1][0] * mat[2][1]) - (mat[2][0] * mat[1][1]);
			mat[1][0] = -((mat[0][1] * mat[2][2]) - (mat[2][1] * mat[0][2]));
			mat[1][1] = ((mat[0][0] * mat[2][2]) - (mat[2][0] * mat[0][2]));
			mat[1][2] = -((mat[0][0] * mat[2][1]) - (mat[2][0] * mat[0][1]));
			mat[2][0] = ((mat[0][1] * mat[1][2]) - (mat[1][1] * mat[0][2]));
			mat[2][1] = -((mat[0][0] * mat[1][2]) - (mat[1][0] * mat[0][2]));
			mat[2][2] = ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
			// Now shuffling
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					res.mat[i][j] = mat[j][i];
				}
			}
			return res;
		}
	}// adj body end
	CMatrix& inverseOfMatrix(int size) {
		int temp, det = 0;
		CMatrix inverse(&size, &size);
		if (size == 2) {// if 2 x 2 matrix
			det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
			cout << "\nDeterminnet of the matrix is " << det << endl;
			if (det == 0) {
				cout << "Warning!\nInverse of given matrix does not exist";
			}
			else {
				temp = mat[0][0];
				mat[0][0] = mat[1][1];
				mat[1][1] = temp;
				mat[0][1] = -mat[0][1];
				mat[1][0] = -mat[1][0];
				//cout << "\n inverse\n";
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 2; j++) {
						int var = mat[i][j];
						int res = var / det;
						inverse.mat[i][j] = res;
					}
				}
			}//inner else end
			return inverse;
		} //if body end
		else if(size==3){
			rows = columns = 3;
			int x, y, z;;
			x = (mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]));
			y = (-mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]));
			z = (mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]));
			det = x + y + z;
			cout << "\nDeterminnet of the matrix is " << det << endl;
			if (det == 0) {
				cout << "\nError inverse of given matrix does not exist\n";
			}
			else {//co-factors
				mat[0][0] = ((mat[1][1] * mat[2][2]) - (mat[1][2] * mat[2][1]));
				mat[0][1] = -((mat[1][0] * mat[2][2]) - (mat[2][0] * mat[1][2]));
				mat[0][2] = ((mat[1][0] * mat[2][1]) - (mat[2][0] * mat[1][1]));
				mat[1][0] = -((mat[0][1] * mat[2][2]) - (mat[2][1] * mat[0][2]));
				mat[1][1] = ((mat[0][0] * mat[2][2]) - (mat[2][0] * mat[0][2]));
				mat[1][2] = -((mat[0][0] * mat[2][1]) - (mat[2][0] * mat[0][1]));
				mat[2][0] = ((mat[0][1] * mat[1][2]) - (mat[1][1] * mat[0][2]));
				mat[2][1] = -((mat[0][0] * mat[1][2]) - (mat[1][0] * mat[0][2]));
				mat[2][2] = ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
				//cout << "\n\n After adjoint values of matrix are \n";
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						int var = mat[j][i];
						int res;
						res = var / det;
						inverse.mat[i][j] = res;
					}
				}
			}
			return inverse;
		}//outer else body end
	}
	int rankOfMatrix() {
		int rank = rows;
		for (int i = 0; i < rows; i++) {
			int sum = 0;
			for (int j = 0; j < columns; j++) {
				if (mat[i][j] == 0) {
					sum = sum + 1;
					if (sum % columns == 0)
						--rank;
				}
			}
		}
		return rank;
	}// rank body end
	CMatrix& transposeOfMatrix() {
		//for transpse
		CMatrix transpose(&columns, &rows);//because in transpose rows
		// change into columns
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				transpose.mat[j][i] = mat[i][j];
			}
		}
		return transpose;
	}//transpose body end

	void symmOrSkewSymm() {
		int x = 0, y = 0;
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				if (mat[i][j] == mat[j][i]) {
					x++;
				}
			}
		}
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				 if (mat[i][j] == -mat[j][i]) {
					y++;
				}
			}
		}
		int s = rows * columns;
		if (x == s)
			cout << "\nThe matrix is  symmetric\n";
		else if (y == s)
			cout << "\nThe matrix is skew-symmetrix\n";
		else {
			cout << "\nThe matrix is neither symmetric nor skew-symmetrix\n";
			displayMatrix();
		}
	}//symmetric and skew-symmetric body end

	string matrixOrder() {
		string order;
		order = to_string(rows) + " by " + to_string(columns);
		return order;
	}

	int determinant(int matrix[3][3], int n) {
		int det = 0;
		int submatrix[3][3];
		if (n == 2)
			return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
		else {
			for (int x = 0; x < n; x++) {
				int subi = 0;
				for (int i = 1; i < n; i++) {
					int subj = 0;
					for (int j = 0; j < n; j++) {
						if (j == x)
							continue;
						submatrix[subi][subj] = matrix[i][j];
						subj++;
					}
					subi++;
				}
				det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
			}
		}
		return det;
	}
};//class CMatrix end

void gotoxy(int xCoord, int yCorrd)
{
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = xCoord;     // defining x-axis
	coordinates.Y = yCorrd;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void myIntro() {
	cout << "\n\t**WELCOME TO MATRIX MANIPULATION SYSTEM***\n";
	gotoxy(35, 15);
	cout << "\n\nCODED BY: ZIA UD DIN";
	gotoxy(35, 11);
	cout << "STUDENT OF BAHRIA UNIVERSITY";
	gotoxy(33, 14);
	cout << "A SHORT SUMMARY";
	gotoxy(35, 17);
	cout << "OOP PROJECT";
	cout << "\n\nCAMPUS : ISLAMABAD\n";
	_getche();
}
void showMenu() {//Menu on run commnand
	system("cls");
	cout << "[[[***** Matrix manipulation system *******]]] \n";
	cout << "\n\tMAIN MENU......\n";
	cout << " [[[[[**SELECT***]] \n";
	cout << "\n\t 1: Checking matrix Order";
	cout << "\n\t 2: Checking singular and non-singular matrices";
	cout << "\n\t 3: Operations on matrices ";
	cout << "\n\t 4: Determinent of a ordered matrix **";
	cout << "\n\t 5: Adjoint of matrix";
	cout << "\n\t 6: Trasnpose matriax";
	cout << "\n\t 7: Checking the matrix is symmetric or skew-symmetric";
	cout << "\n\t 8: Inverse of a matrix **";
	cout << "\n\t r: To find rank of Matrix";
	cout << "\n\t a: To assing a matrix to another";
	cout << "\n\t e:To display an elemement from a matrix\n";
	cout << "\n\t Press ESCAPE key to EXIT Program";
	cout << "\n\n\tPlease Select  Option (0...8,r,s,a) \n\n";
	cout << "Your option :  ";
}

// main body start
int main()
{
	srand(time(NULL));
	int Matrix[3][3];
	myIntro();//just to welcome
	int rows, columns, size;
	CMatrix A, B;//Three objwcts created
	CMatrix* ptrBase;
	char userChoice;
	while (true)//while infinite loop
	{
		showMenu();
		userChoice = _getche();
		switch (userChoice)
		{
		case '1':
		{ cout << "\n";
		cout << "\nFinding order of a matrix**";
		cout << "\n\tEnter rows of matrix : "; cin >> rows;
		cout << "Enter columns of matrix : "; cin >> columns;
		assert(rows > 1 || columns > 1);
		CMatrix orderOfMatrix(&rows, &columns);
		string order;
		order = orderOfMatrix.matrixOrder();
		cout << "Order of the matrix is " << order << endl;
		cout << " The matrix of the given order is like that\n\n";

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int x = rand() % 10;
				cout << "   " << x;
			}cout << endl << endl;
		}cout << "\n";
		}break;

		case '2':
		{
		cout << "\n**Checking singular or non-singular**";
		cout << "\n\tEnter size of matrix : ";
		cin >> size;
		assert(size > 1);
		A.setRowsColumns(&size, &size);
		cout << "ENter matrix elements :\n";
		A.inputMatrix();
		bool det = A.operator!();
		if (det) {
			cout << "\nThe matrix is non-singular and its inverse exist\n";
		}
		else {
			cout << "The matrix is singular and its inverse does'nt exist\n";
		}
		}break;

		case '3':
		{ cout << "\n";
		char operation;
		cout << "Enter Operation on matrices (+,-,*) :  ";
		cout << "\nDivide a matrix by a number enter / \n";
		cout << "\nCheck  two matrices are identical enter =\n";
		cout << "\n\t\tYour operation : ";
		operation = _getche();
		cout << "\n";
		switch (operation) {//inner swtich start
		case '+':
		{ cout << "\nEnter rows,columns of matrix A\n";
		A.enterRC();
		cout << "Please enter the numbers you want to put \n"
			<< "\tinto a Matrix A (it should look like a matrix graph)." << endl;
		A.inputMatrix();
		cout << "\nEnter rows,columns of matrix A\n";
		B.enterRC();
		//for second 2D array
		cout << "\nEnter the elements of matrix B accordingly\n";
		B.inputMatrix();
		CMatrix add = A + B;//Adding objects
		cout << "\n Sum of tow matrices is \n";
		cout << "   is given by \n";
		add.displayMatrix(); cout << "\n";

		}break;
		case '-': {
			cout << "\nEnter rows,columns of matrix A\n";
			A.enterRC();
			cout << "Please enter the numbers you want to put \n"
				<< "\tinto a Matrix A (it should look like a matrix graph)." << endl;
			A.inputMatrix();
			cout << "\nEnter rows,columns of matrix B\n";
			B.enterRC();
			//for second 2D array
			cout << "\nEnter the elements of matrix B accordingly\n";
			B.inputMatrix();
			CMatrix	subtraction = A - B;//subtracting objects
			cout << "\n difference of tow matrices is \n";
			cout << "   is given by \n";
			subtraction.displayMatrix(); cout << "\n";
		}break;		  
		case '*': {
			cout << "\nFor multiplication remember that**\n"
				<< "Columns of first matrix shoud equal to rows of second.\n";
			cout << "\nFor matrix A\n";
			A.enterRC();
			cout << "Please enter the numbers you want to put into A\n";
			A.inputMatrix();
			cout << "\nFor matrix B\n";
			B.enterRC();
			cout << "\nEnter the elements of matrix B accordingly\n";
			B.inputMatrix();
			cout << "\n Element of matrix A\n";
			A.displayMatrix();
			cout << "\n Element of matrix B\n";
			B.displayMatrix();
			CMatrix res= A*B;
			cout << "\n Multipication of two matrices \n is ***\n\nA x B=\n";
			res.displayMatrix();
		}break;
		case '/': { int n;
			cout << "\nEnter the integer that divide the matrix\n";
			cin >> n;
			A.enterRC();
			cout << "\nEnter element of matrix A \n";
			A.inputMatrix();
			cout << "\nOriginal matrix is \n";
			A.displayMatrix(); cout << endl;
			CMatrix ans = A.operator/(n);
			cout << "\nThe resulted matrix is \n";
			ans.displayMatrix(); cout << endl;
		}
		case '=': {
			int sizeB;
			cout << "\nFor this matrices order should be equal\n";
			cout << "Enter size of Matrix A : ";
			cin >> size;
			cout << "Enter size of Matrix A : ";
			cin >> sizeB;
			bool check;
			if (size == sizeB) {
				A.setRowsColumns(&size, &size);
				B.setRowsColumns(&sizeB, &sizeB);
				cout << "\nEnter the elements of matrix A\n";
				A.inputMatrix();
				cout << "\nEnterelements of matrix B\n";
				B.inputMatrix();
				cout << "Elements of matrix A\n";
				A.displayMatrix();
				cout << "Elements of matrix B\n";
				B.displayMatrix();
				check = A.operator== (B);
				if (check)
					cout << "The Matrices are equal\n";
				else
					cout << "The matrices are unequal\n";
			}
			else
				cout << "\nOrder of the matrices is unequal\n";
		}break;
		default:
			cout << "\nWarning! invalid opeartion\n";
		}//inner swtich end 
		}// case 3 end
		break;


		case '4':
		{ cout << "\n";
		cout << "****[ Finding Determinents of square matrix ]****\n";
		int size, determinent;
		int i = 0, j = 0;
		cout << "Enter size of the matrix : ";
		cin >> size;
		CMatrix det(&size, &size);
		int Matrix[3][3];
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				cout << "  Enter row[" << i << "][" << j << "] : ";
				cin >> Matrix[i][j];
			}
		}cout << "\nThe matrix entered is \n\n";
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				cout << "  " << Matrix[i][j];
			}cout << endl;
		}
		determinent = det.determinant(Matrix, size);
		cout << "\nDeterminant of the matrix of size " << size << " is " << determinent << endl;
		if (determinent == 0)
			cout << "This matrix is not invertible as the determinant is zero";
		else
			cout << "This matrix is invertible as the determinant is not zero";
		}break;//case 4 end


		case '5':
		{
		cout << "\nFor this matrix should be square\n";
		cout << "Enter size of the matrix: ";
		cin >> size;
		A.setRowsColumns(&size, &size);
		cout << "Enter matrix elements : \n";
		A.inputMatrix();
		CMatrix adj = A.adjointOfMatrix(size);
		cout << "\n adj(A) is \n";
		adj.displayMatrix();
		cout << endl;
		}break;

		case '6':
		{    cout << "\n";
		cout << "\n** Finding transose of a matrix**";
		cout << "\nEnter rows,columns of the matrix\n";
		A.enterRC();
		cout << "\nEnter elements of the matrix\n";
		A.inputMatrix(); 
		cout << "\n Original matrix is \n";
		A.displayMatrix(); 
		CMatrix trans = A.transposeOfMatrix();
		cout << "\n Transpose of the matrix is \n";
		trans.displayMatrix();
		cout << "\n";
		}break;


		case '7':
		{
		cout << "\n";
		int size;
		cout << "Enter size of the matrix : ";
		cin >> size;
		A.setRowsColumns(&size, &size);
		cout << "Enter the matrix elements\n";
		A.inputMatrix();
		cout << "\nOriginal matrix  is \n";
		A.displayMatrix();
		CMatrix transpose(&size, &size);
		transpose = A.transposeOfMatrix();
		cout << "\nTHe matrix transpose is \n";
		transpose.displayMatrix();//To display traanspose of matrix
		cout << endl;
		transpose.symmOrSkewSymm();//
		}break;

		case '8':
		{cout << "\n"; CMatrix E;
		cout << "ENter size of square matrix : ";
		cin >> size;
		E.setRowsColumns(&size, &size);
		cout << "\nEnter matrix elements \n";
		E.inputMatrix();
		cout << "\nOriinal matrix is \n";
		E.displayMatrix();
		CMatrix result = E.inverseOfMatrix(size);
		cout << "\n Inverse of the matrix is \n";
		result.displayMatrix(); cout << endl;
		}break;

		case 'r': {
			int matrixRank;
			cout << "\n";
			cout << "Rank is the number of non-zero rows in a matrix\n";
			CMatrix rank;
			rank.enterRC();
			rank.inputMatrix();
			cout << "\nThe matrix is \n"; rank.displayMatrix(); cout << endl;
			matrixRank = rank.rankOfMatrix();
			cout << "\n Rank of the matrix is " << matrixRank << endl;
		}break;

		case 'a': 
		{
			cout << "\nEnter the matrix rows : ";
			cin >> rows;
			cout << "Enter the matrix cols : ";
			cin >> columns;
			A.setRowsColumns(&rows, &columns);
			cout << "Enter matrix elements \n";
			A.inputMatrix();
			CMatrix newMatrix = (A.operator=(A));
			cout << "\nThe new matrix is \n";
			newMatrix.displayMatrix();
		}break;

		case 'e': {
			A.enterRC();
			cout << "Enter the matrix values\n";
			A.inputMatrix();
			cout << "\nEnter rows of the element : ";
			cin >> rows;
			cout << "\nEnter coloumn of the elemtent : ";
			cin >> columns;
			int element = A.operator()(rows - 1, columns - 1);	
			cout << "\nThe element is " << element << endl;
		}break;

		case ESCAPE:
		{
			cout << "\n\t PProgram exited successfully!\n";
			exit(2);
		}
		default: {
			cout << "\nWarning!! invalid option\n";
		} break;

		}//outer switch body end
		char Hold = _getche();

	} // infinite while body closed
	cout << "\n\n";
	system("pause");
	return 0;
}


