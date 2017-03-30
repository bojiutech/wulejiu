/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/


package com.hn.market.core;


import android.content.ClipData;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Bitmap.Config;
import android.graphics.PorterDuff.Mode;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v4.content.FileProvider;
import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import com.hn.HNMarket.R;



/**
 * Utilities related to loading/saving contact photos.
 *
 */
public class PhotoUtils {
    private static final String TAG = "ContactPhotoUtils";

    private static final String PHOTO_DATE_FORMAT = "'IMG'_yyyyMMdd_HHmmss";

    /**
     * Generate a new, unique file to be used as an out-of-band communication
     * channel, since hi-res Bitmaps are too big to serialize into a Bundle.
     * This file will be passed (as a uri) to other activities (such as the gallery/camera/
     *  cropper/etc.), and read by us once they are finished writing it.
     */
    
    
    /**
     * 产生图片临时存取的Uri
     * @param context
     * @return
     */
    public static Uri generateTempImageUri(Context context, String name) {
        /*final String  fileProviderAuthority = context.getResources().getString(
                R.string.photo_file_provider_authority);
        Log.i("<<", fileProviderAuthority);*/
        return FileProvider.getUriForFile(context, name,
                new File(pathForTempPhoto(context, generateTempPhotoFileName())));
    }

    /**
     * 产生裁剪图片临时的存取Uri
     * @param context
     * @return
     */
    public static Uri generateTempCroppedImageUri(Context context, String name) {
        /*final String  fileProviderAuthority = context.getResources().getString(
                R.string.photo_file_provider_authority);*/
        return FileProvider.getUriForFile(context, name,
                new File(pathForTempPhoto(context, generateTempCroppedPhotoFileName())));
    }

    /**
     * 获取图片临时路径
     * @param context
     * @param fileName
     * @return
     */
    private static String pathForTempPhoto(Context context, String fileName) {
        final File dir = context.getCacheDir();
        dir.mkdirs();
        final File f = new File(dir, fileName);
        return f.getAbsolutePath();
    }

    /**
     * 产生图片临时文件名
     * @return
     */
    private static String generateTempPhotoFileName() {
        final Date date = new Date(System.currentTimeMillis());
        SimpleDateFormat dateFormat = new SimpleDateFormat(PHOTO_DATE_FORMAT, Locale.US);
        return "ContactPhoto-" + dateFormat.format(date) + ".jpg";
    }

    /**
     * 产生裁剪后图片的临时文件名
     * @return
     */
    private static String generateTempCroppedPhotoFileName() {
        final Date date = new Date(System.currentTimeMillis());
        SimpleDateFormat dateFormat = new SimpleDateFormat(PHOTO_DATE_FORMAT, Locale.US);
        return "ContactPhoto-" + dateFormat.format(date) + "-cropped.jpg";
    }

    /**
     * Given a uri pointing to a bitmap, reads it into a bitmap and returns it.
     * @throws FileNotFoundException
     */
    public static Bitmap getBitmapFromUri(Context context, Uri uri) throws FileNotFoundException {
        final InputStream imageStream = context.getContentResolver().openInputStream(uri);
             byte[] data=compressBitmap(BitmapFactory.decodeStream(imageStream));
            return BitmapFactory.decodeByteArray(data, 0, data.length);
        
    }

    /**
     * Creates a byte[] containing the PNG-compressed bitmap, or null if
     * something goes wrong.
     */
    public static byte[] compressBitmap(Bitmap bitmap) {
        final int size = bitmap.getWidth() * bitmap.getHeight() * 4;
        final ByteArrayOutputStream out = new ByteArrayOutputStream(size);
        try {
            bitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
            out.flush();
            out.close();
            return out.toByteArray();
        } catch (IOException e) {
            Log.w(TAG, "Unable to serialize photo: " + e.toString());
            return null;
        }
    }
    
    
    /**
	 * 产生圆形图片
	 * 
	 * @param bitmap
	 * @param roundPx
	 * @return
	 */
	public static Bitmap getRoundedCornerBitmap(Bitmap bitmap, float roundPx) {
		int w = bitmap.getWidth();
		int h = bitmap.getHeight();
		Bitmap output = Bitmap.createBitmap(w, h, Config.ARGB_8888);
		Canvas canvas = new Canvas(output);
		final int color = 0xff424242;
		final Paint paint = new Paint();
		final Rect rect = new Rect(0, 0, w, h);
		final RectF rectF = new RectF(rect);
		paint.setAntiAlias(true);
		canvas.drawARGB(0, 0, 0, 0);
		paint.setColor(color);
		canvas.drawRoundRect(rectF, roundPx, roundPx, paint);
		paint.setXfermode(new PorterDuffXfermode(Mode.SRC_IN));
		canvas.drawBitmap(bitmap, rect, rect, paint);
		return output;
	}
	
	
    /**
     * 裁剪图片需要设置的的参数
     * @param intent
     * @param photoSize
     */
    public static void addCropExtras(Intent intent, int outputX, int outputY) {
        /*intent.putExtra("crop", "true");
        intent.putExtra("scale", true);
        intent.putExtra("scaleUpIfNeeded", true);
        intent.putExtra("aspectX", 1);
        intent.putExtra("aspectY", 1);
        intent.putExtra("outputX", photoSize);
        intent.putExtra("outputY", photoSize);*/
    	
    	intent.putExtra("crop", "true");  
        intent.putExtra("aspectX", outputX);  
        intent.putExtra("aspectY", outputY);  
        intent.putExtra("outputX", outputX);   
        intent.putExtra("outputY", outputY); 
        intent.putExtra("outputFormat", "JPEG");
        intent.putExtra("noFaceDetection", true);
        intent.putExtra("return-data", true); 
    }

    /**
     * Adds common extras to gallery intents.
     *
     * @param intent The intent to add extras to.
     * @param photoUri The uri of the file to save the image to.
     */
    public static void addPhotoPickerExtras(Intent intent, Uri photoUri) {
        intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
        intent.addFlags(Intent.FLAG_GRANT_WRITE_URI_PERMISSION |
                Intent.FLAG_GRANT_READ_URI_PERMISSION);
        intent.setClipData(ClipData.newRawUri(MediaStore.EXTRA_OUTPUT, photoUri));
    }

    /**
     * Given an input photo stored in a uri, save it to a destination uri
     */
    public static boolean savePhotoFromUriToUri(Context context, Uri inputUri, Uri outputUri,
            boolean deleteAfterSave) {
        FileOutputStream outputStream = null;
        InputStream inputStream = null;
        try {
            outputStream = context.getContentResolver().openAssetFileDescriptor(outputUri, "rw")
            		.createOutputStream();
            inputStream = context.getContentResolver().openInputStream(inputUri);

            final byte[] buffer = new byte[16 * 1024];
            int length;
            int totalLength = 0;
            while ((length = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, length);
                totalLength += length;
            }
            inputStream.close();
            outputStream.flush();
            outputStream.close();
            Log.v(TAG, "Wrote " + totalLength + " bytes for photo " + inputUri.toString());
        } catch (IOException e) {
            Log.e(TAG, "Failed to write photo: " + inputUri.toString() + " because: " + e);
            return false;
        } 
        
        return true;
    }
}


