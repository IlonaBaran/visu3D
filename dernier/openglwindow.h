#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLWidget>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class openglwindow :public QOpenGLWidget {
    Q_OBJECT

    public:
        openglwindow(QWidget *parent = 0);
        ~openglwindow();

        void initializeGL();
        void paintGL();

        // Appel des méthodes d'affichae des objets
        void draw(QString selectedValue, QString selectedFile);

        // Interaction utilisateur : translation, rotation, zoom et dezoom
        void wheelEvent(QWheelEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

        // Affichage des types d'objets demandés + points & cube pour des tets
        void points();
        void cube();
        void obj(QString selectedfile);
        void nuage(QString selectedfile);
        void cityjson(QString selectedfile);

        void projection();
        void initializeGlEnable();
        void initializeGlClear();

        // Récupérer le type d'objet à selectionner et le fichier à visualiser
        void setSelectedValue(const QString& selectedvalue, const QString& selectedfile);
        void setSelectedValueBis(const float& n1, const float& n2, const float& n3);

    private:
        // Récupérer le type d'objet à selectionner et le fichier à visualiser
        QString selectedValue;
        QString selectedFile;

        // Indicateurs de rotation activée et de translation activée
        bool rotateActivated;
        bool translateActivated;

        // Position de la souris à l'instant t et à t-1
        QPointF lastMousePos;
        QPoint currentMousePos;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        float zoomFactor; // Facteur de zoom

        // couleur de fond
        float n1;
        float n2;
        float n3;

};

#endif // OPENGLWINDOW_H



