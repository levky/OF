

#include "ParticleManager.h"

ParticleManager::ParticleManager() {
}


// ------------------------------------------ set texture coords
void ParticleManager::setParticleTexCoords(int i, float columnID, float rowID) {
	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	if(columnID > cellColls) columnID = cellColls;
	if(rowID    > cellRows)	 rowID	  = cellRows;
	
	if(columnID < 0) columnID = 0;
	if(rowID < 0)	 rowID	  = 0;
	
	
	
	// get the cell image width
	float cellWidth  = texW / cellRows;
	float cellHeight = texH / cellColls;
	
	float row = rowID;
	float col = columnID;
	
	// P1
	texcords[(i*4)+0].u = (cellWidth * row)		/ texW;
	texcords[(i*4)+0].v = (cellHeight * col)	/ texH;
	
	// P2
	texcords[(i*4)+1].u = ((cellWidth * row)	+ cellWidth)	/ texW;
	texcords[(i*4)+1].v = (cellHeight * col)	/ texH;
	
	// P2
	texcords[(i*4)+2].u = ((cellWidth * row) + cellWidth)		/ texW;
	texcords[(i*4)+2].v = ((cellHeight * col) + cellHeight)	/ texH;	
	
	// P2
	texcords[(i*4)+3].u = (cellWidth * row)		/ texW;
	texcords[(i*4)+3].v = ((cellHeight * col)+cellHeight)	/ texH;	
	
	
}

// ------------------------------------------ set color
void ParticleManager::setParticleColor(int i, float r, float g, float b, float a) {
	
	
	if(i < 0) i = 0;
	if(i > MAX_PARTICLES) i = MAX_PARTICLES;
	
	
	// Color 1
	color[(i*4)+0].r = r;
	color[(i*4)+0].g = g;
	color[(i*4)+0].b = b;
	color[(i*4)+0].a = a;
	
	// Color 2
	color[(i*4)+1].r = r;
	color[(i*4)+1].g = g;
	color[(i*4)+1].b = b;
	color[(i*4)+1].a = a;
	
	// Color 3
	color[(i*4)+2].r = r;
	color[(i*4)+2].g = g;
	color[(i*4)+2].b = b;
	color[(i*4)+2].a = a;
	
	// Color 4
	color[(i*4)+3].r = r;
	color[(i*4)+3].g = g;
	color[(i*4)+3].b = b;
	color[(i*4)+3].a = a;
	
}

// ------------------------------------------ set position
void ParticleManager::setParticlePos(int i, float px, float py, float pz) {
	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	
	// P1
	pos[(i*4)+0].x = px;
	pos[(i*4)+0].y = py;
	pos[(i*4)+0].z = pz;
	
	// P2
	pos[(i*4)+1].x = px + dim[i];
	pos[(i*4)+1].y = py;
	pos[(i*4)+1].z = pz;
	
	// P2
	pos[(i*4)+2].x = px + dim[i];
	pos[(i*4)+2].y = py + dim[i];
	pos[(i*4)+2].z = pz;
	
	// P2
	pos[(i*4)+3].x = px;
	pos[(i*4)+3].y = py + dim[i];
	pos[(i*4)+3].z = pz;
	
	
	
}

// ------------------------------------------ set size of particle
void ParticleManager::setParticleSize(int i, float particleDim) {
	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	dim[i] = particleDim;
}

// ------------------------------------------ add to the current position
void ParticleManager::addPosition(int i, float x, float y, float z) {
	
	if(i < 0)				i = 0;
	if(i > MAX_PARTICLES)	i = MAX_PARTICLES;
	
	
	// P1
	pos[(i*4)+0].x += x;
	pos[(i*4)+0].y += y;
	pos[(i*4)+0].z += z;
	
	// P2
	pos[(i*4)+1].x += x;
	pos[(i*4)+1].y += y;
	pos[(i*4)+1].z += z;
	
	// P2
	pos[(i*4)+2].x += x;
	pos[(i*4)+2].y += y;
	pos[(i*4)+2].z += z;
	
	// P2
	pos[(i*4)+3].x += x;
	pos[(i*4)+3].y += y;
	pos[(i*4)+3].z += z;
	
	
	
}

// ------------------------------------------ load textures
void ParticleManager::loadTexture(string path, int cellsInRow, int cellsInCol) {

	ofDisableArbTex();
	texture.loadImage(path);
	ofEnableArbTex();
	
	texW = texture.getWidth();
	texH = texture.getHeight();
	
	cellRows  = cellsInRow;
	cellColls = cellsInCol; 
}



// ------------------------------------------ init
void ParticleManager::init() {
	
	
	
	printf("-------------------------------\n");
	
	printf("Max Particles: %i\n", MAX_PARTICLES);
	printf("Pos Size: %i\n", MAX_PARTICLES*4);
	
	printf("-------------------------------\n");
	
	
	
	// Init All The Particles Values
	for(int i=0; i<MAX_PARTICLES; i++) {
		
		// Set the size of the particle
		setParticleSize(i, ofRandom(5, 10));
		
		// The Color Data
		setParticleColor(i, 1, 1, 1, 1);
		
		
		// Position and Texture
		float px = ofRandom(-100, 100);
		float py = ofRandom(-100, 100);
		float pz = ofRandom(-100, 100);
		setParticlePos(i, px, py, pz);
		
		
		// The Texture Coords
		setParticleTexCoords(i, (int)ofRandom(0, 2), (int)ofRandom(0, 2));
		
		
		// Velocity and accelaration
		acc[i][0] = ofRandom(-1.0, 1.0);
		acc[i][1] = ofRandom(-1.0, 1.0);
		acc[i][2] = 0;//ofRandom(-1.0, 1.0);
		
		vel[i][0] = ofRandom(-1.0, 1.0);
		vel[i][1] = ofRandom(-1.0, 1.0);
		vel[i][2] = 0;//ofRandom(-1.0, 1.0);
		
		
		// The Damping
		damping[i] = 0.2;
		
		
		// The Life of the Particle
		life[i][0] = ofRandom(0.3, 1.0);
		life[i][1] = ofRandom(0.01, 0.04);
	}
	
	
	
	
	// Setup the VBO
	
	glGenBuffersARB(3, &particleVBO[0]);
	
	// color
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*4*sizeof(float), color, GL_STREAM_DRAW_ARB);
	
	// vertices
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*3*sizeof(float), pos, GL_STREAM_DRAW_ARB);
	
	// texture coords
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (MAX_PARTICLES*4)*2*sizeof(float), texcords, GL_STREAM_DRAW_ARB);
	
}


// ------------------------------------------	
void ParticleManager::update() {
	

	for(int i=0; i<MAX_PARTICLES; i++) {
		
		
		vel[i][0] += acc[i][0];
		vel[i][1] += acc[i][1];
		vel[i][2] += acc[i][2];
		
		addPosition(i, vel[i][0], vel[i][1], vel[i][2]);
		
		vel[i][0] *= damping[i];
		vel[i][1] *= damping[i];
		vel[i][2] *= damping[i];
	
		// fade by the life rate
		life[i][0] -= life[i][1];
		setParticleColor(i, 1.0, 1.0, 1.0, life[i][0]);
		
		if(life[i][0] <= 0.0) {
			
			
			// Set the size of the particle
			setParticleSize(i, ofRandom(3.0, 10.0));
			
			// The Color Data
			setParticleColor(i, 1, 1, 1, 1);
			
			
			// Position and Texture
			float px = ofRandom(-100, 100);
			float py = ofRandom(-100, 100);
			float pz = ofRandom(-100, 100);
			setParticlePos(i, px, py, pz);
			
			
			// The Texture Coords
			setParticleTexCoords(i, (int)ofRandom(0, 2), (int)ofRandom(0, 2));
			
			
			// Velocity and accelaration
			acc[i][0] = ofRandom(-1.0, 1.0);
			acc[i][1] = ofRandom(-1.0, 1.0);
			acc[i][2] = ofRandom(-1.0, 1.0);
			
			vel[i][0] = ofRandom(-1.0, 1.0);
			vel[i][1] = ofRandom(-1.0, 1.0);
			vel[i][2] = ofRandom(-1.0, 1.0);
			
			
			// The Damping
			damping[i] = 0.2;
			
			
			// The Life of the Particle
			life[i][0] = ofRandom(0.3, 1.0);
			life[i][1] = ofRandom(0.001, 0.004);
			
		}
	}
	
}

// ------------------------------------------ Add Particles
void ParticleManager::addParticles(int amt, float _x, float _y, float _z) {
	
}

// ------------------------------------------
void ParticleManager::render() {
	
	
	// ofSetColor(255, 0, 0);
	/*
	 for (int i=0; i<MAX_PARTICLES; i++) {
	 
	 
	 ofSetColor(0xffffff);
	 
	 
	 ofEnableArbTex();
	 texture.getTextureReference().bind();
	 glBegin(GL_QUADS);
	 
	 float td = 64.0;
	 float pd = ofNormalize(32, 0.0, td);
	 
	 
	 // P1
	 glVertex3f(pos[(i*4)+0].x,
	 pos[(i*4)+0].y,
	 pos[(i*4)+0].z);
	 
	 glTexCoord2f(0, 0);
	 
	 
	 
	 
	 // P2
	 glVertex3f(pos[(i*4)+1].x,
	 pos[(i*4)+1].y,
	 pos[(i*4)+1].z);
	 
	 glTexCoord2f(0.0, pd);
	 
	 
	 
	 // P3
	 glVertex3f(pos[(i*4)+2].x,
	 pos[(i*4)+2].y,
	 pos[(i*4)+2].z);
	 
	 glTexCoord2f(pd, pd);
	 
	 
	 // P4
	 glVertex3f(pos[(i*4)+3].x,
	 pos[(i*4)+3].y,
	 pos[(i*4)+3].z);
	 
	 glTexCoord2f(pd, 0.0);
	 
	 glEnd();
	 texture.getTextureReference().unbind();
	 ofDisableArbTex();
	 }
	 */
	
	
	
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	// bind tex coors
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[2]);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*2*sizeof(float), texcords);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	
	
	// bind color
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[0]);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*4*sizeof(float), color);
	glColorPointer(4, GL_FLOAT, 0, 0);
	
	
	// bind vertices [these are quads]
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, particleVBO[1]);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, (MAX_PARTICLES*4)*3*sizeof(float), pos);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	
	
	// draw the vbo
	glDisable(GL_DEPTH_TEST);
		ofEnableArbTex();	
	
	ofEnableAlphaBlending();
	texture.getTextureReference().bind();

	glDrawArrays(GL_QUADS, 0, MAX_PARTICLES*4);
	
	texture.getTextureReference().unbind();
	ofDisableAlphaBlending();
	
	ofDisableArbTex();
	glEnable(GL_DEPTH_TEST);
	
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glDisable(GL_TEXTURE_2D);
	
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	
	
}

