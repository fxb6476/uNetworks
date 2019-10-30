//
// Created by hivemind on 10/29/2019.
//

//
// Created by hivemind on 10/28/2019.
//
//in progress for a technical init of used in state of the art
int init_weights_xavier(matrix *mat){
    mat->data = (float **)calloc(mat->row, sizeof(float *));
    if(!mat->data){
        printf("Error allocating main data array!\n");
        return -1;
    }

    for(int i = 0; i < mat->row; i++) {
        mat->data[i] = (float *)calloc(mat->col, sizeof(float));
        if(!mat->data){
            printf("Error allocating sub array in data #%d!\n", i);
            return -1;
        }
    }

    for(int i=0; i < mat->row; i++){
        for(int j=0; j < mat->col; j++){
            mat->data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    return 0;
}

matrix*conv2d(matrix input,matrix filters,int filt_size,char pad_type, int stride)
{
    if(pad_type == 'z')
    {
        //identify padding amount
        int pad_size = (filt_size-1)/2;
        //identify padding type
        int pad_type =0
        //create a tmp matrix with modified dimension
        int tmp_row = input->row+pad_size*2;
        int tmp_col = input->col+pad_size*2;
        float **tmp = (float **)calloc(tmp_row, sizeof(float *));
        //pad the matrix with correct type
        for(int i=0; i < tmp_row; i++)
        {

            for(int j=0; j < tmp_col; j++)
            {
                if(i<pad_size || i>pad_size+input->row)
                {
                    tmp[i][j]=0
                }
                else if(j<pad_size || j>pad_size+input->col)
                {
                    tmp[i][j]=0
                }
                else
                {
                    tmp[i][j]=input[i][j]
                }
            }


        }


    }
    else
    {
        printf("unsoported padding type\n");
        return m1
    }
    //free up the data
    for(int i=0; i < input->row; i++)
    {
        free(input->data[i]);
    }

    //create a temp2 to hold the conv values
    int tmp_row2 = m1->row;
    int tmp_col2 = m1->col;
    int filter_row = filters->row
    int filter_col = filters->col
    float **tmp2 = (float **)calloc(tmp_row, sizeof(float *));

    for (int l = 0; l <tmp_row2 ; ++l)
    {

        for (int m = 0; m <tmp_col2 ; ++m)
        {


            for (int i = 0; i < tmp_row; i++)
            {
                float count = 0.0;
                for (int j = 0; j < tmp_col; j++)
                {
                    count += (filters->data[i][j] * tmp2->data[i + l][j + m]);
                    //printf("%.1f\n", count);
                }
                tmp2[i][j] = count;
            }
        }

    }

    m1->row = tmp_row;
    m1->col = tmp_col;
    m1->data = (float **)calloc(m1->row, sizeof(float *));
    for(int i = 0; i < m1->row; i++)
    {
        m1->data[i] = (float *)calloc(m1->col, sizeof(float));
    }

    //Copy tmp data into new m1 matrix with new mem-architecture...
    for(int i=0; i < m1->row; i++)
    {
        for(int j=0; j < m1->col; j++)
        {
            m1->data[i][j] = tmp2[i][j];
        }
    }

    //Free tmp data because we are all done...
    for(int i=0; i < tmp_row; i++)
    {
        free(tmp[i]);
    }
    free(tmp);

    //Free tmp data because we are all done...
    for(int i=0; i < tmp_row; i++)
    {
        free(tmp2[i]);
    }
    free(tmp);
    return m1;


}


matrix*pooling(matrix *m1, char type)
{
    //average max global average
    switch











}