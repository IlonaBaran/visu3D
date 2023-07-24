#include "openglwindow.h"

#include "glm/detail/type_vec.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

openglwindow::openglwindow(QWidget *parent) : QOpenGLWidget(parent){
    zoomFactor = -1.0f;
}

openglwindow::~openglwindow(){
}

void openglwindow::projection(){
    glClearColor(n1, n2, n3, 1.0f);

    glm::vec3 cameraPosition(0.0f, 0.0f, 0.0f); // Position de la caméra (l'œil)
    glm::vec3 targetPosition(-1.0f, -1.0f, -1.0f); // Point à regarder (cible)
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // Vecteur "vers le haut" de la caméra
    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, targetPosition, cameraUp);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(viewMatrix));

    // Appliquer le facteur de zoom à la matrice de projection
    /*
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f) * zoomFactor;
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));
    */
}

void openglwindow::initializeGlEnable(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void openglwindow::initializeGlClear(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_CULL_FACE);
    glClear(GL_DEPTH_TEST);
}


void openglwindow::initializeGL() {
    initializeGlEnable();
    projection();
}

void openglwindow::paintGL() {
    draw(selectedValue, selectedFile);
    update();
}

void openglwindow::setSelectedValue(const QString& selectedvalue, const QString& selectedfile) {
    selectedValue = selectedvalue;
    selectedFile = selectedfile;
}

void openglwindow::setSelectedValueBis(const float& num1, const float& num2, const float& num3) {
    n1 = num1;
    n2 = num2;
    n3 = num3;
}

void openglwindow::wheelEvent(QWheelEvent *event){
    int scroll = event->angleDelta().y();

    if (scroll > 0) {
        zoomFactor *= 1.1f; // Augmenter le facteur de zoom pour zoomer
    } else if (scroll < 0) {
        zoomFactor *= 0.9f; // Diminuer le facteur de zoom pour dézoomer
    }
}

void openglwindow::mousePressEvent(QMouseEvent *event){
    // Vérifier quel bouton de la souris est enfoncé
    if (event->button() == Qt::LeftButton) {
        rotateActivated = true; // Activer la rotation
        translateActivated = false; // Désactiver la translation
    } else if (event->button() == Qt::RightButton) {
        translateActivated = true; // Activer la translation
        rotateActivated = false; // Désactiver la rotation
    }
}

void openglwindow::mouseMoveEvent(QMouseEvent *event){
    QPoint currentMousePos = event->pos();
    lastMousePos = currentMousePos;
}

void openglwindow::draw(QString selectedValue, QString selectedFile)
{
    if (selectedValue == "cube") {
        cube();
    } else if (selectedValue == "points") {
        points();
    } else if (selectedValue == "objet") {
        obj(selectedFile);
    } else if (selectedValue == "nuage") {
        nuage(selectedFile);
    } else if (selectedValue == "cityjson") {
        cityjson(selectedFile);
    } else {
        // rendu par défaut
        float translationSpeed = 0.001f; // Vitesse de translation
        float rotationSpeed = 0.1f; // Vitesse de rotation

        float dx = currentMousePos.x() - lastMousePos.x();
        float dy = currentMousePos.y() - lastMousePos.y();

        float translationOffset = dx * translationSpeed;
        float translationOffsetY = dy * translationSpeed;

        float rotationAngleX = dx * rotationSpeed;
        float rotationAngleY = dy * rotationSpeed;

        initializeGlClear();
        projection();

        if (rotateActivated) {
            glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
            glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
            glRotatef(rotationAngleX, 0.0f, 0.0f, 1.0f);
        } else if (translateActivated) {
            glTranslatef(translationOffset, translationOffsetY, 0.0f);
        }

        glPointSize(50.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glEnd();

        update();
    }
}

void openglwindow::points()
{
    float translationSpeed = 0.001f;
    float rotationSpeed = 0.1f;

    float dx = currentMousePos.x() - lastMousePos.x();
    float dy = currentMousePos.y() - lastMousePos.y();

    float translationOffset = dx * translationSpeed;
    float translationOffsetY = dy * translationSpeed;

    float rotationAngleX = dx * rotationSpeed;
    float rotationAngleY = dy * rotationSpeed;

    initializeGlClear();
    projection();

    if (rotateActivated) {
        glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
        glRotatef(rotationAngleX, 0.0f, 0.0f, 1.0f);
    } else if (translateActivated) {
        glTranslatef(translationOffset, translationOffsetY, 0.0f);
    }

    glPointSize(50.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glEnd();
}


void openglwindow::cube()
{
    float translationSpeed = 0.001f;
    float rotationSpeed = 0.1f;

    float dx = currentMousePos.x() - lastMousePos.x();
    float dy = currentMousePos.y() - lastMousePos.y();

    float translationOffset = dx * translationSpeed;
    float translationOffsetY = dy * translationSpeed;

    float rotationAngleX = dx * rotationSpeed;
    float rotationAngleY = dy * rotationSpeed;

    initializeGlClear();
    projection();

    if (rotateActivated) {
        glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
        glRotatef(rotationAngleX, 0.0f, 0.0f, 1.0f);
    } else if (translateActivated) {
        glTranslatef(translationOffset, translationOffsetY, 0.0f);
    }

    // Dessiner un cube
    glBegin(GL_QUADS);

    // Face avant
    glColor3f(0.4f, 0.1f, 0.4f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Face arrière
    glColor3f(0.9f, 0.0f, 0.7f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Face gauche
    glColor3f(0.2f, 0.2f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Face droite
    glColor3f(1.0f, 0.4f, 0.3f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Face supérieure
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Face inférieure
    glColor3f(0.7f, 0.9f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();
}


void openglwindow::nuage(QString selectedfile)
{
    // Variables pour stocker les coordonnées des points
    QVector<float> vertices;

    // Charger le fichier PLY
    QFile file(selectedfile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }

    // Lire le contenu du fichier ligne par ligne
    QTextStream in(&file);
    QString line;
    bool isVertexData = false;

    while (!in.atEnd()) {
        line = in.readLine();

        // Boucle pour trouver quand le header du fichier .ply se termine
        if (line.contains("end_header")) {
            isVertexData = true;
            continue;
        }

        if (isVertexData) {
            QStringList coordinates = line.split(" ");
            if (coordinates.size() >= 3) {
                float x = coordinates[0].toFloat();
                float y = coordinates[1].toFloat();
                float z = coordinates[2].toFloat();

                vertices.append(x);
                vertices.append(y);
                vertices.append(z);
            }
        }
    }
    file.close();

    float translationSpeed = 0.001f;
    float rotationSpeed = 0.1f;

    float dx = currentMousePos.x() - lastMousePos.x();
    float dy = currentMousePos.y() - lastMousePos.y();

    float translationOffset = dx * translationSpeed;
    float translationOffsetY = dy * translationSpeed;

    float rotationAngleX = dx * rotationSpeed;
    float rotationAngleY = dy * rotationSpeed;

    initializeGlClear();
    projection();

    if (rotateActivated) {
        glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
        glRotatef(rotationAngleX, 0.0f, 0.0f, 1.0f);
    } else if (translateActivated) {
        glTranslatef(translationOffset, translationOffsetY, 0.0f);
    }

    glPointSize(20.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < vertices.size(); i += 3) {
        float x = vertices[i];
        float y = vertices[i + 1];
        float z = vertices[i + 2];
        glVertex3f(x, y, z);
    }
    glEnd();
}



void openglwindow::obj(QString selectedfile)
{

    float translationSpeed = 0.001f;
    float rotationSpeed = 0.1f;

    float dx = currentMousePos.x() - lastMousePos.x();
    float dy = currentMousePos.y() - lastMousePos.y();

    float translationOffset = dx * translationSpeed;
    float translationOffsetY = dy * translationSpeed;

    float rotationAngleX = dx * rotationSpeed;
    float rotationAngleY = dy * rotationSpeed;

    initializeGlClear();
    projection();

    if (rotateActivated) {
        glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
        glRotatef(rotationAngleX, 0.0f, 0.0f, 1.0f);
    } else if (translateActivated) {
        glTranslatef(translationOffset, translationOffsetY, 0.0f);
    }

    // Charger le fichier OBJ
    QFile file(selectedfile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Impossible d'ouvrir le fichier OBJ.";
        return;
    }

    // Variables pour stocker les coordonnées des vertices et les indices des faces
    QVector<glm::vec3> vertices;
    QVector<unsigned int> indices;

    // Lire le contenu du fichier ligne par ligne
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        // Ignorer les lignes qui ne commencent pas par "v " ou "f "
        if (!line.startsWith("v ") && !line.startsWith("f ")) {
            continue;
        }

        // Lire les coordonnées des vertices
        if (line.startsWith("v ")) {
            QStringList coordinates = line.split(" ");
            if (coordinates.size() >= 4) {
                float x = coordinates[1].toFloat();
                float y = coordinates[2].toFloat();
                float z = coordinates[3].toFloat();
                vertices.append(glm::vec3(x, y, z));
            }
        }
        // Lire les indices des faces (triangles)
        else if (line.startsWith("f ")) {
            QStringList faceIndices = line.split(" ");
            if (faceIndices.size() >= 4) {
                // Ignorer les faces avec plus de 3 indices (les quadrilatères, etc.)
                if (faceIndices.size() > 4) {
                    qDebug() << "Le fichier OBJ contient des faces non triangulaires, qui ne sont pas prises en charge.";
                    file.close();
                    return;
                }

                // Lire les indices de chaque sommet de la face
                for (int i = 1; i < faceIndices.size(); ++i) {
                    QString vertexIndexStr = faceIndices[i].split("/").at(0);
                    unsigned int vertexIndex = vertexIndexStr.toUInt() - 1; // Soustraire 1 car les indices dans les fichiers OBJ commencent généralement à 1
                    indices.append(vertexIndex);
                }
            }
        }
    }

    file.close();

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.3f);
    for (unsigned int i = 0; i < indices.size(); ++i) {
        unsigned int vertexIndex = indices[i];
        glm::vec3 vertex = vertices[vertexIndex];
        glVertex3f(vertex.x * 0.5, vertex.y * 0.5, vertex.z * 0.5);
        qDebug() << vertex.x <<  ", " << vertex.y << ", " << vertex.z ;
    }
    glEnd();
}

void openglwindow::cityjson(QString selectedfile)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
