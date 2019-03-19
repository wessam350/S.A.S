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
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button save ;
    private EditText email;
    private EditText password ;
    private TextView textView ;
    private EditText username;
    private EditText phonenum;


    private ProgressDialog progressDialog;

    private FirebaseAuth firebaseAuth;
    private DatabaseReference databaseReference;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);




//        if (firebaseAuth.getCurrentUser() != null){
//            finish();
//            startActivity(new Intent(getApplicationContext(),ProfileActivity.class));
////Intent intent = new Intent(MainActivity.this ,ProfileActivity.class);
////startActivity(intent);
//        }
        firebaseAuth =FirebaseAuth.getInstance();



        progressDialog = new ProgressDialog(this);

        databaseReference = FirebaseDatabase.getInstance().getReference();

        phonenum =(EditText)findViewById(R.id.phonenum);
        username =(EditText)findViewById(R.id.username);

        save = (Button)findViewById(R.id.savedata);

        email = (EditText)findViewById(R.id.email);
        password = (EditText)findViewById(R.id.password);

        textView =(TextView)findViewById(R.id.textView);

        save.setOnClickListener(this);
        textView.setOnClickListener(this);


    }

    private void registerUser(){


//
//               String pho = phonenum.getText().toString();
//        String usname= username.getText().toString();
//        String emm =email.getText().toString();
//        String pw =password.getText().toString();
//        userinfo objinfo = new userinfo(pho,usname , emm , pw);
//        FirebaseUser user = firebaseAuth.getCurrentUser();
//        databaseReference.child(user.getUid()).setValue(objinfo);
//        Toast.makeText(this,"info saved " ,Toast.LENGTH_LONG).show();
//
//            Intent intent = new Intent(this, loginpage.class);
//            startActivity(intent);


        String emil = email.getText().toString().trim();
        String pass = password.getText().toString().trim();

        if (TextUtils.isEmpty(emil)){

            Toast.makeText(this,"please enter your email,",Toast.LENGTH_SHORT).show();
            return;
        }
        if (TextUtils.isEmpty(pass)){
            Toast.makeText(this,"please enter your password,",Toast.LENGTH_SHORT).show();
            return;
        }

        progressDialog.setMessage("Registering user...");
        progressDialog.show();

        firebaseAuth.createUserWithEmailAndPassword(emil,pass).addOnCompleteListener(this,new OnCompleteListener<AuthResult>() {
            @Override
            public void onComplete(@NonNull Task<AuthResult> task) {
                if (task.isSuccessful()){
                    String pho = phonenum.getText().toString();
                    String usname= username.getText().toString();
                    String emm =email.getText().toString();
                    String pw =password.getText().toString();
                    userinfo objinfo = new userinfo(pho,usname , emm , pw);
                    FirebaseUser user = firebaseAuth.getCurrentUser();
                    databaseReference.child(user.getUid()).setValue(objinfo);
                    Toast.makeText(MainActivity.this,"info saved " ,Toast.LENGTH_LONG).show();
                                     startActivity(new Intent(getApplicationContext(),ProfileActivity.class));

            }else{
                    Toast.makeText(MainActivity.this,"alredy registered,",Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(MainActivity.this,loginpage.class);
                    startActivity(intent);
                }
                progressDialog.dismiss();
//                String pho = phonenum.getText().toString();
//                String usname= username.getText().toString();
//                String emm =email.getText().toString();
//                String pw =password.getText().toString();
//                userinfo objinfo = new userinfo(pho,usname , emm , pw);
//                FirebaseUser user = firebaseAuth.getCurrentUser();
//                databaseReference.child(user.getUid()).setValue(objinfo);
//                Toast.makeText(MainActivity.this,"info saved " ,Toast.LENGTH_LONG).show();
//                progressDialog.dismiss();

            }
        });


    }

    @Override
    public void onClick(View v) {
        if (v == save){
            registerUser();


        }
        if (v == textView){
        startActivity(new Intent(this,loginpage.class));

        }
    }
}
