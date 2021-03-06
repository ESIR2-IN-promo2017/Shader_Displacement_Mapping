// atomicGL
//----------------------------------------------------------------------------------------
// author: AL				
// contact: amaury.louarn@homnomnom.fr
// version: 0.1
// current version date: 2016-01-12
//----------------------------------------------------------------------------------------
// atomicGLDistanceMap
//----------------------------------------------------------------------------------------

// constructor
//------------------------
// inputs
//------------------------
// dataArray:   array containing the data to include in the texture
// aagl:		atomicGL context


atomicGLDistanceMap = function(dataArray, height, width, aagl){
	// debug
	// console.log("atomicGLDistanceMap::constructor()");
	// attributes
	// -------------------------------------------------
	// local context
	this.agl = aagl ;
	// texture type
	this.type = "displacement" ;

	// ogl texture
    this.texture = aagl.gl.createTexture();

    var dataTypedArray = new Uint8Array(dataArray);
    aagl.gl.bindTexture(aagl.gl.TEXTURE_2D, this.texture);
    var type = aagl.gl.LUMINANCE;
    aagl.gl.texImage2D(aagl.gl.TEXTURE_2D, 0, type, width, height, 0, type, aagl.gl.UNSIGNED_BYTE, dataTypedArray);
    aagl.gl.generateMipmap(aagl.gl.TEXTURE_2D);
    aagl.gl.bindTexture(aagl.gl.TEXTURE_2D, null);
    this.loaded = true;
}
