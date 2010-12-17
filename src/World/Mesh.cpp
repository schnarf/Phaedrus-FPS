#include "common.h"
#include "System/VFS.h"
#include "World/Mesh.h"
#include "World/Resources.h"
#include "Render/GL.h"

using Math::Vertex; using Math::VertexRef;

//==================================================
//! Construct a mesh from a file
//==================================================
World::Mesh::Mesh( const string& strFilename ) {
	/*float cubez= 0.0f;
	m_pVertices.push_back( VertexRef(new Vertex(-1.0f, -1.0f, cubez)) );
	m_pVertices.push_back( VertexRef(new Vertex(1.0f, -1.0f, cubez)) );
	m_pVertices.push_back( VertexRef(new Vertex(1.0f, 1.0f, cubez)) );
	m_pVertices.push_back( VertexRef(new Vertex(-1.0f, 1.0f, cubez)) );
	m_pVertices.push_back( VertexRef(new Vertex(1.0f, -1.0f, cubez - 2.0f)) );
	m_pVertices.push_back( VertexRef(new Vertex(1.0f, 1.0f, cubez - 2.0f)) );

	{
		MeshFace face;
		face.m_pTexture= ResourceManager::Get()->GetTexture( "brk.bmp" );
		face.m_uNumVertices= 4;
		
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[0], TextureCoords(0.0f, 0.0f)) );
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[1], TextureCoords(1.0f, 0.0f)) );
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[2], TextureCoords(1.0f, 1.0f)) );
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[3], TextureCoords(0.0f, 1.0f)) );
		
		m_Faces.push_back( face );
	}
	
	{
		MeshFace face;
		face.m_pTexture= ResourceManager::Get()->GetTexture( "ocean.bmp" );
		face.m_uNumVertices= 4;
		
		float cubez= -4.0f;
		m_pVertices.push_back( VertexRef(new Vertex(-1.0f, -1.0f, cubez)) );
		m_pVertices.push_back( VertexRef(new Vertex(1.0f, -1.0f, cubez)) );
		m_pVertices.push_back( VertexRef(new Vertex(1.0f, 1.0f, cubez)) );
		m_pVertices.push_back( VertexRef(new Vertex(-1.0f, 1.0f, cubez)) );
		

		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[1], TextureCoords(0.0f, 0.0f)) );
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[4], TextureCoords(1.0f, 0.0f)) );
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[5], TextureCoords(1.0f, 1.0f)) );
		face.m_Vertices.push_back( MeshFaceVertex(m_pVertices[2], TextureCoords(0.0f, 1.0f)) );
		
		m_Faces.push_back( face );
	}*/
	
	loadFromMD3( strFilename );
	
	m_strFilename= strFilename;
}


//==================================================
//! Render this mesh (rendering thread)
//==================================================
void World::Mesh::Render() {
	for( vector<MeshFace>::iterator it= m_Faces.begin(); it != m_Faces.end(); ++it ) {
		it->Render();
	}
}


//==================================================
//! Render this face (rendering thread)
//==================================================
void World::MeshFace::Render() {
	// Bind the texture
	m_pTexture->Bind();
	
	// Now render the face
	glBegin( GL_POLYGON );
	
		for( uint i=0; i<m_uNumVertices; ++i  ) {
			const Vertex* pVtx= m_Vertices[i].pVertex.get();
			const TextureCoords& tex= m_Vertices[i].texCoords;
			
			glTexCoord2f( tex.U, tex.V );
			glVertex3f( pVtx->X(), pVtx->Y(), pVtx->Z() );
		}
	
	glEnd();
}


namespace MD3 {

	struct Frame; struct Tag; struct Surface;
	struct Shader; struct Triangle; struct TexCoord; struct VertexNorm;

	#pragma pack(1)
	struct vec3 {
		float x, y, z;
	};

	struct MD3 {
		int Ident;
		int Version;
		byte Name[64];
		int Flags;
		int NumFrames;
		int NumTags;
		int NumSurfaces;
		int NumSkins;
		int OffFrames;
		int OffTags;
		int OffSurfaces;
		int OffEof;
		
		Frame* pFrames;
		Tag* pTags;
		Surface* pSurfaces;
		
	}; // end struct MD3
	
	struct Frame {
		vec3 MinBounds;
		vec3 MaxBounds;
		vec3 Origin;
		float Radius;
		char Name[16];		
	}; // end struct Frame
	
	struct Tag {
		char Name[64];
		vec3 Origin;
		vec3 Axis[3];
	}; // end struct Tag
	
	
	//! The size of a surface without the pointers
	struct Surface {
		int Ident;
		char Name[64];
		int Flags;
		int NumFrames;
		int NumShaders;
		int NumVerts;
		int NumTriangles;
		int OffTriangles;
		int OffShaders;
		int OffTexCoords;
		int OffVertices;
		int OffEnd;
		Shader* pShaders;
		Triangle* pTriangles;
		TexCoord* pTexCoords;
		VertexNorm* pVertices;
	}; // end struct Surface
			
	struct Shader {
		char Name[64];
		int ShaderIndex;
	}; // end struct Shader
	
	struct Triangle {
		int Indices[3];
	}; // end struct Triangle
	
	struct TexCoord {
		float S;
		float T;
	}; // end struct TexCoord
	
	struct VertexNorm {
		short X;
		short Y;
		short Z;
		short N;
	}; // end struct VertexNorm
	#pragma pack()
	
	void CopyBytes( uint uBytes, const byte* pSrc, byte* pDst ) {
		for( uint i=0; i<uBytes; ++i )
			pDst[i]= pSrc[i];
	}
	
	void ReadFrame( byte* pData, Frame* pFrame ) {
		byte* pWrite= reinterpret_cast<byte*>(pFrame);
		for( uint i=0; i<sizeof(Frame); ++i ) {
			pWrite[i]= pData[i];
		}
	}
	
	void ReadSurface( byte* pData, Surface* pSurface ) {
		// Read in the bytes
		byte* pWrite= reinterpret_cast<byte*>(pSurface);
		
		uint uBytes= sizeof(Surface) - 4*4;
		for( uint i=0; i<uBytes; ++i ) {
			pWrite[i]= pData[i];
		}
		
		// Read in Shaders
		pSurface->pShaders= new Shader[pSurface->NumShaders];
		byte* pOffShaders= &pData[pSurface->OffShaders];
		for( uint i=0; i<pSurface->NumShaders; ++i ) {
			CopyBytes( sizeof(Shader), &pOffShaders[i], reinterpret_cast<byte*>(&pSurface->pShaders[i]) );
		}
		
		// Read in Triangles
		pSurface->pTriangles= new Triangle[pSurface->NumTriangles];
		byte* pOffTriangles= &pData[pSurface->OffTriangles];
		for( uint i=0; i<pSurface->NumTriangles; ++i ) {
			CopyBytes( sizeof(Triangle), &pOffTriangles[i], reinterpret_cast<byte*>(&pSurface->pTriangles[i]) );
		}
		
		// Read in TexCoords and Vertices
		pSurface->pTexCoords= new TexCoord[pSurface->NumVerts];
		pSurface->pVertices= new VertexNorm[pSurface->NumVerts];
		byte* pOffTexCoords= &pData[pSurface->OffTexCoords];
		byte* pOffVertices= &pData[pSurface->OffVertices];
		for( uint i=0; i<pSurface->NumVerts; ++i ) {
			CopyBytes( sizeof(TexCoord), &pOffTexCoords[i], reinterpret_cast<byte*>(&pSurface->pTexCoords[i]) );
			CopyBytes( sizeof(VertexNorm), &pOffVertices[i], reinterpret_cast<byte*>(&pSurface->pVertices[i]) );
		}
		
	}
	
	
	
}; // end namespace MD3

//==================================================
//! Load from a Quake 3 MD3 model
//==================================================
void World::Mesh::loadFromMD3( const string& strFilename ) {

	// Load the file from the VFS, this can throw an exception
	vector<byte> raw;
	g_VFS.LoadRaw( strFilename, raw );
	
	bing:
	byte* pRead= &raw[0];
	MD3::MD3 md3;
	byte* pWrite= reinterpret_cast<byte*>(&md3);
	
	// Read information into the md3
	uint uBytes= 64*sizeof(byte) + 11*sizeof(int);
	for( uint i=0; i<uBytes; ++i ) pWrite[i]= pRead[i];
	
	// Read Frames
	md3.pFrames= new MD3::Frame[md3.NumFrames];
	byte* pOffFrames= &raw[md3.OffFrames];
	for( uint i=0; i<md3.NumFrames; ++i ) {
		ReadFrame( pOffFrames, &md3.pFrames[i] );
		pOffFrames+= sizeof(MD3::Frame);
	}
	
	// Read Surfaces
	md3.pSurfaces= new MD3::Surface[md3.NumSurfaces];
	byte* pOffSurfaces= &raw[md3.OffSurfaces];
	for( uint i=0; i<md3.NumSurfaces; ++i ) {
		ReadSurface( pOffSurfaces, &md3.pSurfaces[i] );
		pOffSurfaces+= md3.pSurfaces[i].OffEnd;
	}
	
	if( md3.Flags == 0 ) goto bing;
}