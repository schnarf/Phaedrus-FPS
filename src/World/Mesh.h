#ifndef _WORLD_MESH_H_
#define _WORLD_MESH_H_

#include "common.h"
#include "Math/Vertex.h"
#include "World/Resources.h"

namespace World {

	struct MeshFaceVertex {
		MeshFaceVertex( Math::VertexRef _pVertex, TextureCoords _texCoords ) :
			pVertex( _pVertex ),
			texCoords( _texCoords ) {
		}
		Math::VertexRef pVertex;
		TextureCoords texCoords;
	};

	class MeshFace {
		friend class Mesh;
	public:
		//! Render this face (rendering thread)
		void Render();
	private:
		//! The number of vertices
		uint m_uNumVertices;
	
		//! Our vertices, counter-clockwise
		vector<MeshFaceVertex> m_Vertices;
		//! The texture for this face
		TextureRef m_pTexture;
	};

	class Mesh {
	public:
		//! Construct a mesh from a file
		Mesh( const string& strFilename );
		
		//! Render this mesh (rendering thread)
		void Render();
		
		//! Get this mesh's filename
		inline string GetFilename() const { return m_strFilename; }
	private:
		//! Load from a Quake 3 MD3 model
		void loadFromMD3( const string& strFilename );

		//! The filename this mesh was loaded from
		string m_strFilename;
	
		//! Our shared vertices
		vector<Math::VertexRef> m_pVertices;
	
		//! Our mesh faces
		vector<MeshFace> m_Faces;
	}; // end namespace Mesh
	
	typedef shared_ptr<Mesh> MeshRef;

}; // end namespace World

#endif
