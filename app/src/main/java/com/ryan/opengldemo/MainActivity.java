package com.ryan.opengldemo;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.Settings;
import android.widget.TextView;

import com.ryan.opengldemo.databinding.ActivityMainBinding;
import com.ryan.opengldemo.view.RyGLSurfaceView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("glesdemo");
    }

    private ActivityMainBinding binding;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        binding = ActivityMainBinding.inflate(getLayoutInflater());
//        setContentView(binding.getRoot());
//        TextView v = binding.sampleText;
//        v.setText(stringFromJNI());
        setContentView(new RyGLSurfaceView(this));
        verifyStoragePermission(this);
    }

    public native String stringFromJNI();

    public void verifyStoragePermission(Activity activity) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            if (Environment.isExternalStorageManager()) {
                // 应用程序已经被授予了 MANAGER_EXTERNAL_STORAGE 权限，可以直接访问外部存储
            } else {
                // 应用没有被授予权限，需要提示用户授权
                Intent intent = new Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION);
                Uri uri = Uri.fromParts("package", getPackageName(), null);
                intent.setData(uri);
                startActivity(intent);
            }
        }
    }
}