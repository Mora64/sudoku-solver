#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isCorrect(int row, int col, int num, vector<vector<int>>& grid);
    bool solve(vector<vector<int>>& grid);
    bool isValidPosition(vector<vector<int>>& grid);

private slots:
    void on_Button_clicked();

    void on_reset_clicked();






    void on_solve_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
