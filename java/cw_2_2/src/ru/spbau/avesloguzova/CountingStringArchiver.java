package ru.spbau.avesloguzova;

/**
 * Created by av on 5/26/15.
 */
public class CountingStringArchiver implements StringArchiver {
    @Override
    public String archive(String input) {
        if(input==null||input.isEmpty()){
            return input;
        }
        StringBuilder builder = new StringBuilder();
        int repeats = 1;
        char last = input.charAt(0);
        for (int i = 1; i < input.length(); i++) {
            if(last!=input.charAt(i)){
                char count = (char) repeats;
                builder.append(count).append(last);
                last = input.charAt(i);
                repeats = 1;
            }else{
                repeats++;
            }
        }
        builder.append((char)repeats).append(last);
        return builder.toString();
    }

    @Override
    public String extract(String archived) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < archived.length(); i+=2) {
            int count = (int)archived.charAt(i);
            char last = archived.charAt(i+1);
            for (int j = 0; j < count; j++) {
                builder.append(last);
            }
        }
        return builder.toString();
    }
}
