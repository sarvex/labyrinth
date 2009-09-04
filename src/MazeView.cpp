#include "MazeView.h"

#include "GL/glut.h"

MazeView::MazeView(const Maze &maze, const Vec3<float> &pos,
        const Vec3<float> & size) :
    m_maze(maze),
    m_pos(pos),
    m_size(size)
{
    m_sectorSize.x = size.x / (float)maze.width();
    m_sectorSize.y = size.y / (float)maze.height();
    m_sectorSize.z = size.z;

    m_postSize.x = m_sectorSize.y / 10;
    m_postSize.y = m_sectorSize.x / 10;
    m_postSize.z = m_sectorSize.z * 1.2;

}

MazeView::~MazeView() {
    
}

void MazeView::display() {
    // display the floor

    // display each wall
    for(int x=0; x<m_maze.width(); ++x) {
        for(int y=0; y<m_maze.height(); ++y) {
            // rectangle from m_pos+x*m_sectorSize to m_pos+(x+1)*sectorSize
            Vec3<float> loc( m_pos.x + ((float)x) * m_sectorSize.x,
                m_pos.y + ((float)y) * m_sectorSize.y, 0);

            // floor
            glColor3f(0.1, 0.1, 0.5);
            glBegin(GL_POLYGON);
                glVertex3f(loc.x+m_sectorSize.x, loc.y, loc.z);
                glVertex3f(loc.x+m_sectorSize.x, loc.y+m_sectorSize.y, loc.z);
                glVertex3f(loc.x, loc.y+m_sectorSize.y, loc.z);
                glVertex3f(loc.x, loc.y, loc.z);
            glEnd();
            
            // north
            if( m_maze.cellHasWall(x,y,Maze::South) ) {
                glColor3f(0.1, 0.9, 0.1);
                cuboid(
                    loc+Vec3<float>(m_postSize.x, m_postSize.y, 0),
                    loc+Vec3<float>(m_sectorSize.x-m_postSize.x, m_postSize.y,
                        0),
                    loc+Vec3<float>(m_sectorSize.x-m_postSize.x, -m_postSize.y,
                        0),
                    loc+Vec3<float>(m_postSize.x, -m_postSize.y, 0),
                    m_sectorSize.z);
            }

            // west
            if( m_maze.cellHasWall(x,y,Maze::East) ) {
                glColor3f(0.4, 0.4, 0.1);
                cuboid(
                    loc+Vec3<float>(-m_postSize.x, -m_postSize.y, 0),
                    loc+Vec3<float>(m_postSize.x, -m_postSize.y, 0),
                    loc+Vec3<float>(m_postSize.x, -m_sectorSize.y+m_postSize.y,
                        0),
                    loc+Vec3<float>(-m_postSize.x, -m_sectorSize.y+m_postSize.y,
                        0),
                    m_sectorSize.z);
            }

            // place a post
            glColor3f(0.59, 0.65, 0.74);
            cuboid(
                loc+Vec3<float>(-m_postSize.x, m_postSize.y, 0),
                loc+Vec3<float>(m_postSize.x, m_postSize.y, 0),
                loc+Vec3<float>(m_postSize.x, -m_postSize.y, 0),
                loc+Vec3<float>(-m_postSize.x, -m_postSize.y, 0),
                m_postSize.z);
        }
    }
}

void MazeView::cuboid(Vec3<float> basePt1, Vec3<float> basePt2,
    Vec3<float> basePt3, Vec3<float> basePt4, float height)
{
    // box
    glBegin(GL_QUAD_STRIP);
        glVertex3f(basePt1.x, basePt1.y, basePt1.z);
        glVertex3f(basePt1.x, basePt1.y, basePt1.z+height);
        glVertex3f(basePt2.x, basePt2.y, basePt2.z);
        glVertex3f(basePt2.x, basePt2.y, basePt2.z+height);
        glVertex3f(basePt3.x, basePt3.y, basePt3.z);
        glVertex3f(basePt3.x, basePt3.y, basePt3.z+height);
        glVertex3f(basePt4.x, basePt4.y, basePt4.z);
        glVertex3f(basePt4.x, basePt4.y, basePt4.z+height);
        glVertex3f(basePt1.x, basePt1.y, basePt1.z);
        glVertex3f(basePt1.x, basePt1.y, basePt1.z+height);
    glEnd();

    // put on caps
    glBegin(GL_POLYGON);
        glVertex3f(basePt1.x, basePt1.y, basePt1.z);
        glVertex3f(basePt2.x, basePt2.y, basePt2.z);
        glVertex3f(basePt3.x, basePt3.y, basePt3.z);
        glVertex3f(basePt4.x, basePt4.y, basePt4.z);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(basePt4.x, basePt4.y, basePt4.z+height);
        glVertex3f(basePt3.x, basePt3.y, basePt3.z+height);
        glVertex3f(basePt2.x, basePt2.y, basePt2.z+height);
        glVertex3f(basePt1.x, basePt1.y, basePt1.z+height);
    glEnd();
}
