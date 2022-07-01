#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QList>
#include<QGridLayout>
#include <map>
#include<QMessageBox>

using namespace std;
int counter = 0;
map<QPushButton*,int> but_counter;
map<QPushButton*, pair<int,int>> but_index;
vector<vector<int>> grid = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    for(int i = 0 ; i < 9;i++){
        for(int j = 0; j < 9; j++){
            QPushButton* button = new QPushButton(this);
            button->setFixedSize(50,50);
            ui->gridLayout->addWidget(button, i, j);
            QLayoutItem* item = ui->gridLayout->itemAtPosition(i, j);
            QWidget* widget = item->widget();
            QPushButton* button_click = dynamic_cast<QPushButton*>(widget);
            connect(button_click, SIGNAL(clicked()), this, SLOT(on_Button_clicked()));

            but_counter.insert(make_pair(button, 0));
            but_index.insert(make_pair(button, make_pair(i,j)));

        }
    }






}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Button_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*> (sender());
    auto it = but_counter.find(button);


    auto it_index = but_index.find(button);
    grid[it_index->second.first][it_index->second.second]++;

    it->second += 1;
    int number = it->second;
    button->setText(QString::number(number));


}

void MainWindow::on_reset_clicked()
{
    //for(auto item : but_counter){
        //item.second = 0;
        //item.first->setText("");
    //};
    for(auto it = but_counter.begin(); it != but_counter.end(); ++it) {
        it->second = 0;
        it->first->setText("");
     }
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            grid[i][j] = 0;
        }
    }
    counter=0;
    ui->label->setText("0");
}
bool MainWindow::isCorrect(int row, int col, int num, vector<vector<int>>& grid){
    counter++;
    for (int i = 0; i < 9; i++){

               if (grid[i][col] == num || grid[row][i] == num)
                   return false;
               int rs = row - row % 3;
               int cs = col - col % 3;
               for (int i = rs; i < rs + 3; i++)
               {

                   for (int j = cs; j < cs + 3; j++)
                   {

                       if (grid[i][j] == num)
                           return false;
                   }
               }
           }
           return true;

}


bool MainWindow::solve(vector<vector<int>>& grid){

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)

                {

                    if (grid[i][j] == 0)
                    {
                        for (int val = 1; val <= 9; val++)
                        {

                            if (isCorrect(i, j, val, grid))
                            {
                                grid[i][j] = val;
                                if (solve(grid))
                                {
                                    return true;
                                }
                                else
                                    grid[i][j] = 0;
                            }
                        }
                        return false;
                    }
                }
            }
            return true;
}

bool MainWindow::isValidPosition(vector<vector<int>>& grid){
    for(int i = 0 ; i < 9 ; i ++){
        for(int j = 0 ; j < 9 ; j++){

            if(grid[i][j] == 0) continue;
            for(int x = 0 ; x < 9; x++){

                if(x == j) continue;
                if(grid[i][x] == grid[i][j]) return false;
            }
            for(int y = 0; y < 9;y++){

                if(y == i) continue;
                if(grid[y][j] == grid[i][j]) return false;
            }
            int rs = i - i % 3; //row_start of the square grid
            int cs = j - j % 3;//col_start of the square grid

            for (int x = rs; x < rs + 3; x++){
                for (int y = cs; y < cs + 3; y++){

                   if(x == i && y == j) continue;
                   if (grid[x][y] == grid[i][j])
                      return false;
                }
            }
        }
    }

    return true;
}


void MainWindow::on_solve_clicked()
{
    if(!isValidPosition(grid)){
        QMessageBox::warning(this,"error", "this position isnt validation");
        on_reset_clicked();
        return;
    }
    solve(grid);
    for(int i = 0; i < 9;i++){
        for(int j = 0 ; j < 9;j++){
            QLayoutItem* item = ui->gridLayout->itemAtPosition(i, j);
            QWidget* widget = item->widget();
            QPushButton* button = dynamic_cast<QPushButton*>(widget);
            button->setText(QString::number(grid[i][j]));
        }

    }
    ui->label->setText(QString::number(counter));
}

