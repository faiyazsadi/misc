BEGIN
   FOR cur_rec IN (SELECT object_name, object_type
                     FROM user_objects
                    WHERE object_type IN
                             ('TABLE',
                              'VIEW',
                              'PACKAGE',
                              'PROCEDURE',
                              'FUNCTION',
                              'SEQUENCE',
                              'TYPE',
                              'SYNONYM',
                              'MATERIALIZED VIEW'
                             ))
   LOOP
      BEGIN
         IF cur_rec.object_type = 'TABLE'
         THEN
            EXECUTE IMMEDIATE    'DROP '
                              || cur_rec.object_type
                              || ' "'
                              || cur_rec.object_name
                              || '" CASCADE CONSTRAINTS';
         ELSE
            EXECUTE IMMEDIATE    'DROP '
                              || cur_rec.object_type
                              || ' "'
                              || cur_rec.object_name
                              || '"';
         END IF;
      EXCEPTION
         WHEN OTHERS
         THEN
            DBMS_OUTPUT.put_line (   'FAILED: DROP '
                                  || cur_rec.object_type
                                  || ' "'
                                  || cur_rec.object_name
                                  || '"'
                                 );
      END;
   END LOOP;
END;
/

BEGIN
   FOR cur_syn IN (SELECT synonym_name
                     FROM all_synonyms
                    WHERE table_owner = 'MY_USER')
   LOOP
      BEGIN
         EXECUTE IMMEDIATE 'drop public synonym ' || cur_syn.synonym_name ;
      EXCEPTION
         WHEN OTHERS
         THEN
            DBMS_OUTPUT.PUT_LINE ('Failed to drop the public synonym ' || cur_syn.synonym_name || '! ' || sqlerrm);
      END;
   END LOOP;
END;
/
