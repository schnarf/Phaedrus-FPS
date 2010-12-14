#include "common.h"
#include "World/ParticleSystem.h"
#include "Render/GL.h"

namespace {
	const float PARTICLE_SIZE= 0.5f;
	const uint NUM_PARTICLES= 10000;
	const uint PARTICLE_SPREAD= 100;
	const float GRAVITY= 0.00005f;
}; // end anonymous namespace

//==================================================
//! Initialize the particles
//==================================================
World::ParticleSystem::ParticleSystem() {
	// Allocate
	m_particles.resize( NUM_PARTICLES );
	
	// Initialize
	for( uint i=0; i<m_particles.size(); ++i ) {
		m_particles[i].life= 0.0f;
		m_particles[i].r= 1.0f;
		m_particles[i].g= 0.0f;
		m_particles[i].b= 0.0f;
	}

}


//==================================================
//! De-allocate
//==================================================
World::ParticleSystem::~ParticleSystem() {
}


//==================================================
//! Update the physics
//==================================================
void World::ParticleSystem::PhysicsTick( uint uTimestep ) {
	float dt= (float)uTimestep / 15.0f;

	for( uint i=0; i<m_particles.size(); ++i ) {
		ParticleInfo& particle= m_particles[i];
	
		if( particle.life > 0.0f ) {
			// If the particle is alive, apply physics
			
			// Velocity
			particle.pos+= particle.vel * dt;
			
			// Gravity
			particle.vel.y-= GRAVITY*dt;
			
			// Bounce
			if( particle.pos.y < -1.0f + PARTICLE_SIZE ) {
				particle.pos.y= PARTICLE_SIZE;
				particle.life-= 0.01f;
				particle.vel.y*= -0.6f;
			}
			
			// Life
			particle.life-= (0.0001f * dt);
		} else {
			// If the particle is dead, reset it
			particle.pos= Math::Vector( 0.0f, PARTICLE_SIZE, 0.0f );
			
			float Spread= (float)(rand() % PARTICLE_SPREAD) / 10000.0f;
			float Angle= (float)(rand() % 157) / 100.0f;
			
			particle.vel= Math::Vector( cosf(Angle)*Spread, (float)(rand()%500) / 10000.0f, sinf(Angle)*Spread );
			
			// Randomly reverse x and z for circle
			if( rand()%2 )
				particle.vel.x*= -1.0f;
			
			if( rand()%2 )
				particle.vel.z*= -1.0f;
				
			// Random life and color
			particle.life= (float)(rand() % 100) / 100.0f;
			particle.g= 0.2f + ((float)(rand() % 50) / 100.0f);
		}
	}
}


//==================================================
//! Render the particle system (rendering thread)
//==================================================
void World::ParticleSystem::Render() {

	glDisable( GL_TEXTURE_2D );
	
	glPointSize( 6.0 );
	glEnable( GL_POINT_SMOOTH );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glBegin( GL_POINTS );
		for( uint i=0; i<m_particles.size(); ++i )  {
			ParticleInfo& particle= m_particles[i];
			
			glColor3f( particle.r * particle.life, particle.g * particle.life, particle.b * particle.life );
			glVertex3f( particle.pos.x, particle.pos.y, particle.pos.z );
		}
	glEnd();
	
	glEnable( GL_TEXTURE_2D );

}