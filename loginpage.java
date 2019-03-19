package com.example.a499;

import android.app.ProgressDialog;
import android.content.Intent;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;

public class loginpage extends AppCompatActivity implements View.OnClickListener {

    private Button singin ;
    private EditText emil;
    private EditText pass;
    private TextView textViewsingup;

private FirebaseAuth firebaseAuth;

private ProgressDialog progressDialog ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_loginpage);

        firebaseAuth = firebaseAuth.getInstance();

//        if (firebaseAuth.getCurrentUser() != null){
//            finish();
//            startActivity(new Intent(getApplicationContext(),ProfileActivity.class));
//
//        }

    emil =(EditText)findViewById(R.id.emil);
    pass = (EditText)findViewById(R.id.pass);
    singin=(Button)findViewById(R.id.singin);
    textViewsingup=(TextView)findViewById(R.id.textViewsingup);

    progressDialog = new ProgressDialog(this);

        singin.setOnClickListener(this);
        textViewsingup.setOnClickListener(this);
    }
private void userlogin(){
String email = emil.getText().toString().trim();
String password = pass.getText().toString().trim();


    if (TextUtils.isEmpty(email)){

        Toast.makeText(this,"please enter your email,",Toast.LENGTH_SHORT).show();
        return;
    }
    if (TextUtils.isEmpty(password)){
        Toast.makeText(this,"please enter your password,",Toast.LENGTH_SHORT).show();
        return;
    }

    progressDialog.setMessage("Login user...");
    progressDialog.show();

    firebaseAuth.signInWithEmailAndPassword(email,password).addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
        @Override
        public void onComplete(@NonNull Task<AuthResult> task) {
            progressDialog.dismiss();
            if (task.isSuccessful()){
                finish();
            startActivity(new Intent(getApplicationContext(),ProfileActivity.class));
            }
        }
    });

}
    @Override
    public void onClick(View v) {
        if (v == singin){
            userlogin();
        }
        if(v == textViewsingup){
            finish();
            startActivity(new Intent(this,MainActivity.class));
        }
    }
}
