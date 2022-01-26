//--------------------------------------------------------------------------
//  Project      : w11clubm.ide
//  File Name    : CLUBDAT.H
//  Written by   : Ioan Ghip
//  Created      : 25.10.1994
//  Updated      : 13.10.1995
//--------------------------------------------------------------------------
//  Dest. System : windows
//--------------------------------------------------------------------------
//  Libraries    : raima
//--------------------------------------------------------------------------
//  Data Files   :
//--------------------------------------------------------------------------
//  Remarks
//--------------------------------------------------------------------------
//  
//--------------------------------------------------------------------------

struct club_dataST {
	double  cd_donation;
	double  cd_donation_to_club;
	double  cd_donation_to_bonus;
	double  cd_bank_reg_fee;
	double  cd_futura_reg_fee;
	double  cd_printout_fee;
	double  cd_reading_fee;
	double  cd_extra_fee;
	double  cd_withdrawal_fee;
	double  cd_deposit_fee;
	long  cd_voucher_no;
	long  cd_members_no;
	long  cd_next_member_no;
	long  cd_obs_limit;
	long  cd_view_limit;
	int  cd_voucher_type;
	int  cd_date_type;
	int  cd_first_date;
	int  cd_last_date;
	int  cd_last_year;
	int  cd_initialized;
	int  cd_country_no;
	int  cd_language;
	int  cd_name_type;
	char  cd_currency[4];
};

struct personST {
	int  p_level1;
	int  p_level2;
	int  p_level3;
	char  p_id[15];
	char  p_password[9];
	int  p_club_acces;
	char  p_till_password[9];
};

struct p_keyST {
	char  p_id[15];
	char  p_password[9];
};

struct bank_dataST {
	int  bd_level1;
	char  bd_name[15];
	int  bd_first_date;
	int  bd_last_date;
	int  bd_initialized;
	long  bd_voucher_no;
	double  bd_paid_in;
	double  bd_paid_out;
};

struct dept_dataST {
	int  dd_level1;
	int  dd_level2;
	char  dd_name[15];
	int  dd_first_date;
	int  dd_last_date;
	int  dd_initialized;
	long  dd_voucher_no;
	double  dd_paid_in;
	double  dd_paid_out;
};

struct till_dataST {
	int  td_level1;
	int  td_level2;
	int  td_level3;
	char  td_name[15];
	int  td_first_date;
	int  td_last_date;
	int  td_initialized;
	long  td_voucher_no;
	long  td_payments_no;
	long  td_donation_no;
	long  td_withdrawals_no;
	long  td_deposit_no;
	double  td_paid_from_depo;
	double  td_paid_out_to_with;
	double  td_paid_from_dept;
	double  td_paid_out_to_dept;
	double  td_paid_from_bank;
	double  td_paid_out_to_bank;
	double  td_sold;
};
struct tempST {
	int  t_level1;
	int  t_level2;
	int  t_level3;
	char  t_name[15];
};


struct club_memberST {
	long  m_no;
	char  m_first_name[30];
	char  m_last_name[30];
	char  m_address1[30];
	char  m_address2[30];
	char  m_postal_address[20];
	char  m_id[25];
	char  m_home_tel[21];
	char  m_off_tel[21];
	char  m_registered_by[15];
	int  m_born_date;
	int  m_registr_date;
	int  m_update_date;
	int  m_blocked_date;
	long  m_bunch_no;
	long  m_mrecs[5];
	int  m_mdate[5];
	long  m_recruiter;
	long  m_recruits[9];
	double  m_recruits_acc[9];
	long  m_withdrawal_no;
	long  m_accountr_no;
	long  m_accountp_no;
	long  m_deposit_no;
	long  m_extra_fee_no;
	double  m_withdrawals_amount;
	double  m_bonus_amount;
	double  m_accountr_amount;
	double  m_accountp_amount;
	double  m_deposit;
	double  m_extra_fee;
	int  m_last_date_acc_read;
	int  m_last_date_acc_print;
	int  m_last_date_withdrawal;
	int  m_last_date_deposit;
};
/*
struct logST {
	char  l_id[15];
	int  l_date_in;
	int  l_date_out;
	int  l_time_in;
	int  l_time_out;
};
struct transactionST {
	int  t_date;
	long  t_voucher_no;
	double  t_amount;
	long  t_member_no;
};
*/


