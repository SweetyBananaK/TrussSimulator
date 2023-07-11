#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "trusswidget.hpp"
#include "myscene.hpp"
#include <iostream>
#include <string>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QList>
#include "parser.hpp"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
    ui->addJoint_Button->setEnabled(false);
    ui->deleteJoint_Button->setEnabled(false);
    ui->Emodul_aktiv->setEnabled(false);
    ui->Emodul_speichern->setEnabled(false);
    ui->addForce_Button->setEnabled(false);
    ui->deleteForce_Button->setEnabled(false);
    ui->Knoten_verbinden->setEnabled(false);
    ui->deleteEdge_Button->setEnabled(false);

    ui->X_input->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\t?$)")));
    ui->Y_input->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\t?$)")));
    ui->Joint_locator->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})")));
    ui->Force_x->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,8})(?:\\.\\d{1,4})?$|(^\t?$)")));
    ui->Force_y->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,8})(?:\\.\\d{1,4})?$|(^\t?$)")));
    ui->Force_Locator->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})")));
    ui->Edge_Joint1->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})")));
    ui->Edge_Joint2->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})")));
    ui->thickness->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,8})(?:\\.\\d{1,4})?$|(^\t?$)")));


    connect(ui->myTrussWidget->scene,SIGNAL(sendSignals()),this,SLOT(Mouse_Press_getX()));
    connect(ui->myTrussWidget->scene,SIGNAL(sendSignals()),this,SLOT(Mouse_Press_getY()));
    connect(ui->myTrussWidget,SIGNAL(sendSelectSignals()),this,SLOT(get_SelectedObject()));
    connect(ui->myTrussWidget,SIGNAL(sendClearSignals()),this,SLOT(clearText()));
    connect(ui->myTrussWidget,SIGNAL(sendMoveSignals()),this,SLOT(get_MouseMove()));
    connect(ui->myTrussWidget->scene->menu->actions()[3],SIGNAL(triggered()),this, SLOT(on_addJoint_Button_clicked()));
    connect(ui->myTrussWidget->scene->menu->actions()[4],SIGNAL(triggered()),this, SLOT(on_deleteJoint_Button_clicked()));
    connect(ui->myTrussWidget->scene->menu->actions()[7],SIGNAL(triggered()),this, SLOT(on_deleteEdge_Button_clicked()));
    connect(ui->myTrussWidget->scene->menu->actions()[6],SIGNAL(triggered()),this, SLOT(on_Knoten_verbinden_clicked()));
    connect(ui->myTrussWidget->scene->menu->actions()[10],SIGNAL(triggered()),this, SLOT(on_deleteForce_Button_clicked()));
    connect(ui->myTrussWidget->scene->menu->actions()[9],SIGNAL(triggered()),this, SLOT(addForce_mouse()));
    connect(ui->myTrussWidget->scene->menu->actions()[12],SIGNAL(triggered()),this, SLOT(changeLager_true()));
    connect(ui->myTrussWidget->scene->menu->actions()[13],SIGNAL(triggered()),this, SLOT(changeLager_false()));
    connect(ui->myTrussWidget->scene->menu->actions()[15],SIGNAL(triggered()),this, SLOT(on_Emodul_aktiv_clicked()));
}


MainWindow::~MainWindow(){

    delete ui;
}

    //Slot, "Tragwerk speichern" geklickt. Oeffnet Dialogfenster zum speichern einer Datei, ruft Truss.save_truss(..) auf
void MainWindow::on_actionTragwerk_speichern_triggered(){

    QString file_name = QFileDialog::getSaveFileName(this, tr("Tragwerk speichern"), "new_truss.truss", tr("Tragwerk (*.truss)"));
    //std::cout<< file_name.toStdString() << std::endl;
    //std::string File = file_name.toStdString();
    if(file_name == ""){return;}
    ui->myTrussWidget->current_truss->save_truss(file_name.toStdString());
}

    //Slot, "Tragwerk laden" geklickt. Oeffnet Dialogfenster zum laden einer Datei, loescht aktuelles Targwerk und erstellt neues aus Datei
void MainWindow::on_actionTragwerk_laden_triggered(){

    QString file_name;
    file_name = QFileDialog::getOpenFileName(this,
                tr("Tragwerkladen"), "",
                tr("Tragwerk (*.truss);;All Files (*)")); //filename =

    std::string std_file_name = file_name.toStdString();
    if(std_file_name == ""){return;}

    ui->myTrussWidget->delete_truss(ui->myTrussWidget->current_truss);
    ui->myTrussWidget->current_truss = new Truss(std_file_name);
    ui->myTrussWidget->show_truss(ui->myTrussWidget->current_truss);

    ui->E_modul_input->clear();
}


void MainWindow::on_Emodul_speichern_clicked(){
    std::string file_name = QFileDialog::getSaveFileName(this, tr("E-Modul speichern"), "new_E-Modul.func", tr("E-Modul (*.truss)")).toStdString();
    if(file_name == ""){return;}
    std::string function = ui->E_modul_input->text().toStdString();
    ui->myTrussWidget->current_truss->my_parser->save_function(file_name,function);
}

void MainWindow::on_Emodul_laden_clicked()
{
    QString file_name;
    file_name = QFileDialog::getOpenFileName(this,
                tr("E-Modul laden"), "",
                tr("E-Modul (*.func);;All Files (*)"));

    std::string std_file_name = file_name.toStdString();
    if(std_file_name == ""){return;}

    ifstream temp_func;
    temp_func.open(std_file_name);
    std::string function;
    temp_func >> function;
    ui->E_modul_input->setText(QString::fromStdString(function));
    ui->myTrussWidget->current_truss->my_parser->load_function(std_file_name);
    QMessageBox::critical(this,  "Achtung",  "E-Modul ist geladen!");
}
    //Graut Knopf "Knoten Hinzufuegen" aus wenn kein Text in die Felder eingegeben wurde
void MainWindow::on_X_input_textChanged(const QString &arg1){ //Klickt nur, wenn es Text gibt

    if(ui->X_input->text().isEmpty() || ui->Y_input->text().isEmpty()){
            ui->addJoint_Button->setEnabled(false);
        }
        else{
            ui->addJoint_Button->setEnabled(true);
            QPoint P(ui->X_input->text().toDouble(),ui->Y_input->text().toDouble());
            ui->myTrussWidget->O.setRect(P.x()-3,P.y()-3,6,6);
        }
}


void MainWindow::on_Y_input_textChanged(const QString &arg1){ //Klickt nur, wenn es Text gibt

    if(ui->X_input->text().isEmpty() || ui->Y_input->text().isEmpty()){
            ui->addJoint_Button->setEnabled(false);
        }
        else{
            ui->addJoint_Button->setEnabled(true);
            QPoint P(ui->X_input->text().toDouble(),ui->Y_input->text().toDouble());
            ui->myTrussWidget->O.setRect(P.x()-3,P.y()-3,6,6);
        }
}

    //Slot, Liest Eingaben, fuegt Knoten aktuellem Tragwerk und Scene hinzu
void MainWindow::on_addJoint_Button_clicked(){

    QString x = ui->X_input->text();
    QString y = ui->Y_input->text();

    QString Support = ui->Lager->currentText();
    double S;
    if(Support.toStdString() == "mit Lager") S = -2;
    else S = -1;

    int p = ui->myTrussWidget->current_truss->addJoint(x.toDouble(),y.toDouble(),S);
    ui->myTrussWidget->scene->addItem(ui->myTrussWidget->current_truss->v_joint_ptr[p]);
}

//Slot, Kraft "Hinzufügen" geklickt.
void MainWindow::on_addForce_Button_clicked()
{
    bool isint;
    bool isdouble1;
    bool isdouble2;
    QString sfx = ui->Force_x->text();
    QString sfy = ui->Force_y->text();
    QString sloc = ui->Force_Locator->text();

    int locator = sloc.toInt(&isint,10) - 1;
    if((!isint) | (!ui->myTrussWidget->current_truss->isJoint(locator))){
        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
        return;
    }

    double fx = sfx.toDouble( &isdouble1);
    double fy = sfy.toDouble( &isdouble2);
    if((!isdouble1) || (!isdouble2)){
        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
        return;
      }

    if(ui->myTrussWidget->current_truss->hasForce(locator) == true){
        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
        return;
    }

    ui->myTrussWidget->current_truss->addForce(fx,fy,locator);
    int pos = ui->myTrussWidget->current_truss->v_force_ptr.size() - 1;
    ui->myTrussWidget->scene->addItem(ui->myTrussWidget->current_truss->v_force_ptr[pos]);
}



void MainWindow::get_MouseMove(){

    QString Text1 = "X:";
    QString Text2 = QString::number(ui->myTrussWidget->mousePos.x());
    QString Text12 = Text1 + Text2;

    QString Text3 = "Y:";
    QString Text4 = QString::number(ui->myTrussWidget->mousePos.y());
    QString Text34 = Text3 + Text4;

    ui->Mouse_coordinate1->setText(Text12);
    ui->Mouse_coordinate2->setText(Text34);
}

void MainWindow::Mouse_Press_getX() {

    ui->X_input->setText( QString::number( ui->myTrussWidget->scene->get_Point().x() ) );
}
void MainWindow::Mouse_Press_getY() {

    ui->Y_input->setText( QString::number( ui->myTrussWidget->scene->get_Point().y() ) );
}

void MainWindow::get_SelectedObject() {        
        //fur Knoten
        if(ui->myTrussWidget->Joint_selected != 0) {
            for(std::vector<Joint *>::iterator Joint_iter =ui->myTrussWidget->current_truss->v_joint_ptr.begin();
                    Joint_iter<ui->myTrussWidget->current_truss->v_joint_ptr.end();Joint_iter++) { //the itemIterator cant use get_locator
                if((*Joint_iter)->pos() == ui->myTrussWidget->Joint_selected->pos()) {
                    ui->X_input->setText( QString::number( ui->myTrussWidget->Joint_selected->pos().x() ) );
                    ui->Y_input->setText( QString::number( ui->myTrussWidget->Joint_selected->pos().y() ) );
                    ui->Joint_locator->setText(QString::number( (*Joint_iter)->get_locator()+1));

                    ui->Force_Locator->clear();
                    ui->Force_Locator->setText(QString::number( (*Joint_iter)->get_locator()+1));

                    if(!ui->myTrussWidget->right_click) {
                        if(ui->Edge_Joint1->text().isEmpty() == false && ui->Edge_Joint2->text().isEmpty() == false) {
                            ui->Edge_Joint1->clear();
                            ui->Edge_Joint2->clear();
                        }
                        if(ui->Edge_Joint1->text().isEmpty() == true && ui->Edge_Joint2->text().isEmpty() == true)
                            ui->Edge_Joint1->setText(QString::number( (*Joint_iter)->get_locator()+1));
                        else if(ui->Edge_Joint1->text().isEmpty() == false && ui->Edge_Joint2->text().isEmpty() == true)
                            ui->Edge_Joint2->setText(QString::number( (*Joint_iter)->get_locator()+1));
                        else if(ui->Edge_Joint1->text().isEmpty() == true && ui->Edge_Joint2->text().isEmpty() == false)
                            ui->Edge_Joint1->setText(QString::number( (*Joint_iter)->get_locator()+1));

                        if((*Joint_iter)->get_support() == -2)
                            ui->Lager->setCurrentIndex(0);
                        else
                            ui->Lager->setCurrentIndex(1);
                    }
                    else {
                        ui->Edge_Joint1->clear();
                        ui->Edge_Joint2->clear();
                        ui->Edge_Joint1->setText(QString::number( (*Joint_iter)->get_locator()+1));
                        if((*Joint_iter)->get_support() == -2)
                            ui->Lager->setCurrentIndex(0);
                        else
                            ui->Lager->setCurrentIndex(1);
                    }

                }
            }
        }

    //fur Kanten
    if(ui->myTrussWidget->Edge_selected != 0) {
        clearText();
        for(std::vector<Edge *>::iterator Edge_iter =ui->myTrussWidget->current_truss->v_edge_ptr.begin();
        Edge_iter<ui->myTrussWidget->current_truss->v_edge_ptr.end();Edge_iter++) {
            if((*Edge_iter)->boundingRect().center() == ui->myTrussWidget->Edge_selected->boundingRect().center()) { //update info             
                ui->Edge_Joint1->setText(QString::number( (*Edge_iter)->get_joint_ptr1()->get_locator()+1));
                ui->Edge_Joint2->setText(QString::number( (*Edge_iter)->get_joint_ptr2()->get_locator()+1));
                ui->thickness->setText(QString::number( (*Edge_iter)->get_thickness()));

            }
        }
    }

        //fur Krafte
     if(ui->myTrussWidget->Force_selected != 0) {
            clearText();
            for(std::vector<Force *>::iterator Force_iter =ui->myTrussWidget->current_truss->v_force_ptr.begin();
                    Force_iter<ui->myTrussWidget->current_truss->v_force_ptr.end();Force_iter++) {
                if((*Force_iter)->boundingRect().center() == ui->myTrussWidget->Force_selected->boundingRect().center()) {
                    ui->Force_x->setText(QString::number( (*Force_iter)->get_xforce() ) );
                    ui->Force_y->setText(QString::number( (*Force_iter)->get_yforce() ) );
                    ui->Force_Locator->setText(QString::number( (*Force_iter)->get_joint_ptr()->get_locator()+1 ) );
                }
            }
        }



}


void MainWindow::clearText() {

    ui->X_input->clear();
    ui->Y_input->clear();
    //ui->thickness->clear();
    ui->Joint_locator->clear();
    ui->Edge_Joint1->clear();
    ui->Edge_Joint2->clear();
    force_flag = false;
    ui->Force_x->clear();
    ui->Force_y->clear();
    ui->Force_Locator->clear();
    force_flag = true;
    ui->Lager->setCurrentIndex(0);
}

void MainWindow::on_Joint_locator_textChanged(const QString &arg1) //Klickt nur, wenn es Text gibt
{
    if(ui->Joint_locator->text().isEmpty()){
            ui->deleteJoint_Button->setEnabled(false);
        }
        else{
            ui->deleteJoint_Button->setEnabled(true);
        }
}

void MainWindow::on_deleteJoint_Button_clicked(){ //Delete Joint

    bool isint;
    int locator = ui->Joint_locator->text().toInt(&isint) - 1;
    if(!isint){

        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
        return;
      }

    if(ui->myTrussWidget->current_truss->isJoint(locator)){

        while(ui->myTrussWidget->current_truss->v_joint_ptr[locator]->get_edges().empty() == false){
            int pos1 = ui->myTrussWidget->current_truss->v_joint_ptr[locator]->get_edges()[0]->get_joint_ptr1()->get_locator();
            int pos2 = ui->myTrussWidget->current_truss->v_joint_ptr[locator]->get_edges()[0]->get_joint_ptr2()->get_locator();
            ui->myTrussWidget->scene->removeItem(ui->myTrussWidget->current_truss->v_joint_ptr[locator]->get_edges()[0]);
            ui->myTrussWidget->current_truss->deleteEdge(pos1,pos2);
        }

        int n_forces = ui->myTrussWidget->current_truss->v_force_ptr.size();

        for(int i = n_forces - 1; i >= 0; i--){

            if(ui->myTrussWidget->current_truss->v_force_ptr[i]->get_joint_ptr()->get_locator() == locator){
                ui->myTrussWidget->scene->removeItem(ui->myTrussWidget->current_truss->v_force_ptr[i]);
                ui->myTrussWidget->current_truss->deleteForce(i);
            }
        }

      ui->myTrussWidget->scene->removeItem(ui->myTrussWidget->current_truss->v_joint_ptr[locator]);
      ui->myTrussWidget->current_truss->deleteJoint(locator);
      clearText();
    }
    else {

        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
    }

}

void MainWindow::on_Knoten_verbinden_clicked(){ //addEdge

    bool isint1, isint2, isdouble;
    int locator1 = ui->Edge_Joint1->text().toInt(&isint1) - 1;
    int locator2 = ui->Edge_Joint2->text().toInt(&isint2) - 1;
    double thickness = ui->thickness->text().toDouble(&isdouble);
    if( (!isint1)
        || (!isint2)
        || (!isdouble)
        || (!ui->myTrussWidget->current_truss->isJoint(locator1))
        || (!ui->myTrussWidget->current_truss->isJoint(locator2))
        || (locator1 == locator2)){

        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
        return;
    }

    int check = ui->myTrussWidget->current_truss->isEdge(locator1,locator2);
    if(check == -1){

        ui->myTrussWidget->current_truss->addEdge(locator1,locator2,thickness);
        ui->myTrussWidget->scene->addItem(ui->myTrussWidget->current_truss->v_edge_ptr[ui->myTrussWidget->current_truss->v_edge_ptr.size()-1]);
    }
    else{

        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
    }
}

void MainWindow::on_deleteEdge_Button_clicked(){

    bool isint1, isint2;
    int locator1 = ui->Edge_Joint1->text().toInt(&isint1)-1;
    int locator2 = ui->Edge_Joint2->text().toInt(&isint2)-1;
    //Edge muss removed werden bevor sie gelöscht wird

    if( (!isint1)
        || (!isint2)
        || (!ui->myTrussWidget->current_truss->isJoint(locator1))
        || (!ui->myTrussWidget->current_truss->isJoint(locator2))
        || (locator1 == locator2)){

        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
        return;
      }

    int check = ui->myTrussWidget->current_truss->isEdge(locator1,locator2);
    if(check != -1){

        ui->myTrussWidget->scene->removeItem(ui->myTrussWidget->current_truss->v_edge_ptr[check]);
        ui->myTrussWidget->current_truss->deleteEdge(locator1,locator2);
        clearText();
    }
    else{

        QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
    }
}

void MainWindow::on_actionSimulieren_triggered(bool active){

  if(active){

      bool is_nonlinear = !(ui->radioButton->isChecked());

      ui->myTrussWidget->Simulate(is_nonlinear);

      //Alle Eingabemöglichkeiten blockieren
      ui->groupBox->setEnabled(false);
      ui->groupBox_2->setEnabled(false);
      ui->groupBox_3->setEnabled(false);
      ui->groupBox_4->setEnabled(false);

      //Alle Modi blockieren
      ui->actionConnectionMode->setEnabled(false);
      ui->actionForceMode->setEnabled(false);
      ui->actionJointMode->setEnabled(false);
      ui->actionEraserMode->setEnabled(false);
      //ui->myTrussWidget->setAttribute(Qt::WA_TransparentForMouseEvents,true);

      //Actions für Verwaltung der Ansicht enablen
      ui->actionNeues_Tragwerk_zeigen->setEnabled(true);
      ui->actionVerschiebung_zeigen->setEnabled(true);

      ui->actionNeues_Tragwerk_zeigen->setChecked(true);
      ui->actionVerschiebung_zeigen->setChecked(true);
  }
  else{

      ui->myTrussWidget->delete_truss(ui->myTrussWidget->deformed_truss);

      ui->myTrussWidget->delete_displacement_arrows();

      ui->groupBox->setEnabled(true);
      ui->groupBox_2->setEnabled(true);
      ui->groupBox_3->setEnabled(true);
      ui->groupBox_4->setEnabled(true);
      ui->actionConnectionMode->setEnabled(true);
      ui->actionForceMode->setEnabled(true);
      ui->actionJointMode->setEnabled(true);
      ui->actionEraserMode->setEnabled(true);

      ui->actionNeues_Tragwerk_zeigen->setEnabled(false);
      ui->actionVerschiebung_zeigen->setEnabled(false);

      ui->myTrussWidget->toggle_truss_visibility(ui->myTrussWidget->current_truss, true);
      ui->actionAltes_Tragwerk_zeigen->setChecked(true);

      ui->actionNeues_Tragwerk_zeigen->setChecked(false);
      ui->actionVerschiebung_zeigen->setChecked(false);
      //ui->myTrussWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    }
  update();
}

void MainWindow::on_deleteForce_Button_clicked(){

    bool isint;
    int locator = ui->Force_Locator->text().toInt(&isint) - 1;
    if(!isint){
      QMessageBox::critical(this,  "Achtung",  "Ungültige Eingabe!");
    }

    int n_forces = ui->myTrussWidget->current_truss->v_force_ptr.size();
    for(int i = n_forces - 1; i >= 0; i--){

      if(ui->myTrussWidget->current_truss->v_force_ptr[i]->get_joint_ptr()->get_locator() == locator){

          ui->myTrussWidget->scene->removeItem(ui->myTrussWidget->current_truss->v_force_ptr[i]);
          ui->myTrussWidget->current_truss->deleteForce(i);

        }
  }
  clearText();
}



void MainWindow::on_actionAltes_Tragwerk_zeigen_triggered(bool checked){

    ui->myTrussWidget->toggle_truss_visibility(ui->myTrussWidget->current_truss,checked);
}


void MainWindow::on_actionNeues_Tragwerk_zeigen_triggered(bool checked){

    ui->myTrussWidget->toggle_truss_visibility(ui->myTrussWidget->deformed_truss,checked);
}


void MainWindow::on_actionVerschiebung_zeigen_triggered(bool checked){

    ui->myTrussWidget->toggle_displacement_arrow_visibility(checked);
}


void MainWindow::on_E_modul_input_textChanged(const QString &arg1){

    if(ui->E_modul_input->text().isEmpty()){

        ui->Emodul_aktiv->setEnabled(false);
        ui->Emodul_speichern->setEnabled(false);
    }
    else{
        ui->Emodul_aktiv->setEnabled(true);
        ui->Emodul_speichern->setEnabled(true);
    }
}

void MainWindow::on_actionneues_Tragwerk_triggered(){

    ui->myTrussWidget->delete_truss(ui->myTrussWidget->current_truss);
    ui->myTrussWidget->current_truss = new Truss();
    ui->E_modul_input->clear();
}


void MainWindow::on_Force_x_textChanged(const QString &arg1)
{
    //Enable
    if(ui->Force_x->text().isEmpty() || ui->Force_y->text().isEmpty()){
            ui->addForce_Button->setEnabled(false);
        }
        else{
            ui->addForce_Button->setEnabled(true);
        }
    //Info update
    if(!ui->myTrussWidget->right_click && force_flag) {
    if(ui->Force_Locator->text().isEmpty() == false) {
        if(ui->myTrussWidget->current_truss->hasForce(ui->Force_Locator->text().toInt()-1) == false){
            return;
        }
        else {
            std::vector<Force*>::iterator iter = ui->myTrussWidget->current_truss->v_force_ptr.begin();
            for(;iter != ui->myTrussWidget->current_truss->v_force_ptr.end();iter++) {
                if((*iter)->get_joint_ptr()->get_locator() == ui->Force_Locator->text().toInt()-1)
                    break;
            }
            if(iter != ui->myTrussWidget->current_truss->v_force_ptr.end())
                (*iter)->set_xforce(ui->Force_x->text().toDouble());
            ui->myTrussWidget->viewport()->update();
        }
    }
    }
}

void MainWindow::on_Force_y_textChanged(const QString &arg1)
{
    //Enable
    if(ui->Force_x->text().isEmpty() || ui->Force_y->text().isEmpty()){
            ui->addForce_Button->setEnabled(false);
        }
        else{
            ui->addForce_Button->setEnabled(true);
        }
    //Info update
    if(!ui->myTrussWidget->right_click && force_flag) {
    if(ui->Force_Locator->text().isEmpty() == false) {
        if(ui->myTrussWidget->current_truss->hasForce(ui->Force_Locator->text().toInt()-1) == false){
            return;
        }
        else {
            std::vector<Force*>::iterator iter = ui->myTrussWidget->current_truss->v_force_ptr.begin();
            for(;iter != ui->myTrussWidget->current_truss->v_force_ptr.end();iter++) {
                if((*iter)->get_joint_ptr()->get_locator() == ui->Force_Locator->text().toInt()-1)
                    break;
            }
            if(iter != ui->myTrussWidget->current_truss->v_force_ptr.end())
                (*iter)->set_yforce(ui->Force_y->text().toDouble());
            ui->myTrussWidget->viewport()->update();
        }
    }
    }
}

void MainWindow::on_Force_Locator_textChanged(const QString &arg1)
{
    if(ui->Force_Locator->text().isEmpty()){
            ui->deleteForce_Button->setEnabled(false);
        }
        else{
            ui->deleteForce_Button->setEnabled(true);
        }
}

void MainWindow::on_thickness_textChanged(const QString &arg1)
{
    if(ui->thickness->text().isEmpty()){
        ui->Knoten_verbinden->setEnabled(false);
    }
    else{
        ui->Knoten_verbinden->setEnabled(true);
    }
}

void MainWindow::on_Edge_Joint1_textChanged(const QString &arg1)
{
    if(ui->Edge_Joint1->text().isEmpty() || ui->Edge_Joint2->text().isEmpty()){
        ui->deleteEdge_Button->setEnabled(false);
    }
    else{
        ui->deleteEdge_Button->setEnabled(true);
    }
}

void MainWindow::on_Edge_Joint2_textChanged(const QString &arg1)
{
    if(ui->Edge_Joint1->text().isEmpty() || ui->Edge_Joint2->text().isEmpty()){
        ui->deleteEdge_Button->setEnabled(false);
    }
    else{
        ui->deleteEdge_Button->setEnabled(true);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_F)
        flag = 0;
}

void MainWindow::addForce_mouse() {
    ui->myTrussWidget->right_click = true;
    if(ui->myTrussWidget->current_truss->hasForce(ui->Joint_locator->text().toInt()-1) == true){
        QMessageBox::critical(this,  "Achtung",  "Es gibt einen Kraft schon!");
        return;
      }
    flag = 1;
    double x=ui->myTrussWidget->Joint_selected->x();
    double y=ui->myTrussWidget->Joint_selected->y();
    ui->myTrussWidget->current_truss->addForce(100,0,ui->Joint_locator->text().toInt()-1);
    int pos = ui->myTrussWidget->current_truss->v_force_ptr.size() - 1;
    ui->myTrussWidget->scene->addItem(ui->myTrussWidget->current_truss->v_force_ptr[pos]);

    while(flag) {
         ui->myTrussWidget->current_truss->v_force_ptr[pos]->set_xforce((x-ui->myTrussWidget->mousePos.x())/(Utils::ForceArrowScaling));
         ui->myTrussWidget->current_truss->v_force_ptr[pos]->set_yforce((y-ui->myTrussWidget->mousePos.y())/(Utils::ForceArrowScaling));
         ui->myTrussWidget->viewport()->update();
         ui->Force_x->clear();
         ui->Force_y->clear();
         ui->Force_x->setText(QString::number((x-ui->myTrussWidget->mousePos.x())/(Utils::ForceArrowScaling)));
         ui->Force_y->setText(QString::number((y-ui->myTrussWidget->mousePos.y())/(Utils::ForceArrowScaling)));
         sleep(1);
    }
    ui->myTrussWidget->right_click = false;
}

void MainWindow::sleep(int msec) {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::on_Lager_currentIndexChanged(int index)
{
    if(ui->Joint_locator->text().isEmpty() == false) {
        if(index == 0){
            ui->myTrussWidget->current_truss->v_joint_ptr[ui->Joint_locator->text().toInt()-1]->set_support(-2);
        }
        else {
            ui->myTrussWidget->current_truss->v_joint_ptr[ui->Joint_locator->text().toInt()-1]->set_support(-1);
        }
        ui->myTrussWidget->viewport()->update();
    }
}

void MainWindow::changeLager_true() {
    ui->Lager->setCurrentIndex(0);
    ui->myTrussWidget->viewport()->update();
}
void MainWindow::changeLager_false() {
    ui->Lager->setCurrentIndex(1);
    ui->myTrussWidget->viewport()->update();
}

void MainWindow::on_actionAls_Bild_speichern_triggered(){


    QString fileName = QFileDialog::getSaveFileName(this, tr("Bild speichern"), "unbenannt.png", tr("Bild (*.png)"));

    /*
    QGraphicsView* view = new QGraphicsView(ui->myTrussWidget->scene,this);
    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    pixMap.save(fileName);
    */
    if (!fileName.isNull())
        {
            QPixmap pixMap = this->ui->myTrussWidget->grab();
            pixMap.save(fileName);
        }

}



void MainWindow::on_Emodul_aktiv_clicked()
{
  if(ui->radioButton->isChecked()){
    bool isdouble;
    double new_emodule = ui->E_modul_input->text().toDouble(&isdouble);

    if(isdouble){
        ui->myTrussWidget->current_truss->set_emodule(new_emodule);
        QMessageBox::critical(this,  "Achtung",  "E-Modul aktiviert!");
      }else{
        QMessageBox::critical(this,  "Achtung",  "Keine gültiges E-modul!");
      }

    }else{
      std::string e_modul_string = ui->E_modul_input->text().toStdString();
      if(!ui->myTrussWidget->current_truss->my_parser->set_function(e_modul_string)){
          QMessageBox::critical(this,  "Achtung",  "Keine gültige Funktion!");
      }
      else {
          QMessageBox::critical(this,  "Achtung",  "E-Modul aktiviert!");
      }
    }
}
