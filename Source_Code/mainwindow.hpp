#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override;


private slots:
    void on_actionTragwerk_speichern_triggered();
    void on_actionTragwerk_laden_triggered();


    void on_Emodul_speichern_clicked();


    void on_X_input_textChanged(const QString &arg1);


    void on_Y_input_textChanged(const QString &arg1);

    void on_addJoint_Button_clicked();

    void on_addForce_Button_clicked();

    void on_deleteForce_Button_clicked();


    void get_MouseMove();

    void Mouse_Press_getX();
    void Mouse_Press_getY();

    void get_SelectedObject();
    void clearText();

    void on_Joint_locator_textChanged(const QString &arg1);

    void on_deleteJoint_Button_clicked();

    void on_Knoten_verbinden_clicked();

    void on_deleteEdge_Button_clicked();

    void on_actionSimulieren_triggered(bool checked);

    void on_actionAltes_Tragwerk_zeigen_triggered(bool checked);

    void on_actionNeues_Tragwerk_zeigen_triggered(bool checked);

    void on_actionVerschiebung_zeigen_triggered(bool checked);

    void on_E_modul_input_textChanged(const QString &arg1);

    void on_actionneues_Tragwerk_triggered();


    void on_Force_x_textChanged(const QString &arg1);

    void on_Force_y_textChanged(const QString &arg1);

    void on_Force_Locator_textChanged(const QString &arg1);

    void on_thickness_textChanged(const QString &arg1);

    void on_Edge_Joint1_textChanged(const QString &arg1);

    void on_Edge_Joint2_textChanged(const QString &arg1);

    void addForce_mouse();
    void sleep(int msec);

    void on_Lager_currentIndexChanged(int index);

    void changeLager_true();
    void changeLager_false();

    void on_actionAls_Bild_speichern_triggered();


    void on_Emodul_laden_clicked();

    void on_Emodul_aktiv_clicked();

private:
    Ui::MainWindow *ui;
    int flag;
    bool force_flag=true;
};
#endif // MAINWINDOW_HPP
