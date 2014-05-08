package com.mousebird.maply;

import java.util.TreeSet;

/**
 * This class is used by the MaplyController to reference count textures.
 * It should be entirely invisible to toolkit users.
 * 
 * @author sjg
 *
 */
class TextureManager 
{
	class TextureWrapper implements Comparable<TextureWrapper>
	{
		TextureWrapper(NamedBitmap inBitmap)
		{
			bitmap = inBitmap;
		}
				
		// The bitmap with its unique name
		NamedBitmap bitmap = null;
		// Texture ID in the rendering engine
		long texID = 0;
		// Number of things using it
		int refs = 0;

		@Override
		public int compareTo(TextureWrapper that) 
		{
			return bitmap.name.compareTo(that.bitmap.name);
		}		
	};
	
	TreeSet<TextureWrapper> textures = new TreeSet<TextureWrapper>();
	
	/**
	 * Create a texture or find an existing one corresponding to the named
	 * bitmap.  Returns the texture ID or EmptyIdentity on failure.
	 * @param theBitmap
	 * @param changes
	 * @return
	 */
	long addTexture(NamedBitmap theBitmap, ChangeSet changes)
	{
		// Find an existing one
		TextureWrapper testWrapper = new TextureWrapper(theBitmap);
		if (textures.contains(testWrapper))
		{
			TextureWrapper existingBitmap = textures.floor(testWrapper);
			existingBitmap.refs++;
			return existingBitmap.texID;
		}
		
		// Need to create it
		Texture texture = new Texture();
		if (!texture.setBitmap(theBitmap.bitmap))
			return MaplyController.EmptyIdentity;
		testWrapper.refs = 1;
		testWrapper.texID = texture.getID();
		
		// After we call addTexture it's no longer ours to play with
		changes.addTexture(texture);
		textures.add(testWrapper);
				
		return testWrapper.texID;
	}
	
	/**
	 * Look for the given texture ID, decrementing its reference count or removing it.
	 * @param texID
	 */
	void removeTexture(long texID, ChangeSet changes)
	{
		for (TextureWrapper texWrap: textures)
		{
			if (texWrap.texID == texID)
			{
				texWrap.refs--;
				// Remove the texture
				if (texWrap.refs <= 0)
				{
					changes.removeTexture(texWrap.texID);
					textures.remove(texWrap);
				}
				
				return;
			}
		}
	}
}